gretl_lists_join_with_separator (const int *list1, const int *list2)
{
    int *biglist;
    int i, j, n;

    if (list2 == NULL) {
	return NULL;
    }

    n = (list1 != NULL)? list1[0] : 0;


    n += list2[0] + 1;
    biglist = gretl_list_new(n);

    if (biglist == NULL) {
	return NULL;
    }

    j = 1;

    if (list1 != NULL) {
	for (i=1; i<=list1[0]; i++) {
	    biglist[j++] = list1[i];
	}
    }

    biglist[j++] = LISTSEP;

    for (i=1; i<=list2[0]; i++) {
	biglist[j++] = list2[i];
    }

    return biglist;
}
