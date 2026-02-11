list_sort(PMList *list)
{
	char **arr = NULL;
	PMList *lp;
	unsigned int arrct;
	int i;

	if(list == NULL) {
		return(NULL);
	}

	arrct = list_count(list);
	arr = (char **)malloc(arrct*sizeof(char*));
	for(lp = list, i = 0; lp; lp = lp->next) {
		arr[i++] = (char *)lp->data;
	}

	qsort(arr, (size_t)arrct, sizeof(char *), list_strcmp);

	lp = NULL;
	for(i = 0; i < arrct; i++) {
		lp = list_add(lp, strdup(arr[i]));
	}

	if(arr) {
		free(arr);
		arr = NULL;
	}

	return(lp);
}
