#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct pokemon
{
    int idx;
    char* name;
};

int compare(const void* a,const void* b) {
    return strcmp(((struct pokemon*)a)->name, ((struct pokemon*)b)->name);
}

int compart(const void* a, const void* b) {
    return (((struct pokemon*)a)->idx - ((struct pokemon*)b)->idx);
}

int binary(char* temp, struct pokemon* dict, int low, int high) {
    int mid = (low + high) / 2;
    if (strcmp(temp, (dict + mid)->name) == 0) return (dict + mid)->idx;
    else if (strcmp(temp, (dict + mid)->name) > 0) return binary(temp, dict, mid + 1, high);
    else if (strcmp(temp, (dict + mid)->name) < 0) return binary(temp, dict, low, mid-1);
}

struct pokemon* copyDict(struct pokemon* dict, int n) {
    struct pokemon* copy = (struct pokemon*)malloc(n * sizeof(struct pokemon));
    for (int i = 0; i < n; i++) {
        copy[i].idx = dict[i].idx;
        copy[i].name = (char*)malloc((strlen(dict[i].name) + 1) * sizeof(char));
        strcpy(copy[i].name, dict[i].name);
    }
    return copy;
}

int main() {
    int n;
    int num;
    char temp[20];
    scanf("%d %d", &n, &num);
    struct pokemon* dict = (struct pokemon*)malloc(n * sizeof(struct pokemon));

    for (int i = 0; i < n; i++) {
        scanf("%s", temp);
        (dict+i)->name = (char*)malloc((strlen(temp) + 1) * sizeof(char));
        strcpy((dict + i)->name, temp);
        (dict + i)->idx = i + 1;
    }
    struct pokemon* dict_idx = copyDict(dict, n);
    qsort(dict_idx, n, sizeof(struct pokemon), compart);
    struct pokemon* dict_name = copyDict(dict, n);
    qsort(dict_name, n, sizeof(struct pokemon), compare);

    for (int i = 0; i < num; i++) {
        scanf("%s", temp);
        if (atoi(temp) <= n && atoi(temp) > 0) {
            printf("%s\n", (dict_idx + atoi(temp) - 1)->name);
        }
        else{
            printf("%d\n", binary(temp, dict_name, 0, n - 1));
        }
    }
    free(dict);
    free(dict_idx);
    free(dict_name);
    return 0;
}