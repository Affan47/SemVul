gretl_list_append_term (int **plist, int v)
{
    int *list = NULL;

    if (*plist == NULL) {
	list = gretl_list_new(1);
	if (list != NULL) {
	    list[1] = v;
	}
    } else {
	int oldn = (*plist)[0];

	list = realloc(*plist, (oldn + 2) * sizeof *list);
	if (list != NULL) {
	    list[0] += 1;
	    list[list[0]] = v;
	} else {
	    free(*plist);
	}
    }

    *plist = list;

    return list;
}
