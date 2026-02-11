panel_list_add (const MODEL *orig, const int *add, int *err)
{
    int *newlist = NULL;
    int i;

    if (orig->ci == ARBOND) {
	return arbond_list_add(orig, add, err);
    }

    if (orig->opt & OPT_F) {
	int *panlist;


	panlist = gretl_list_new(orig->list[0] + 1);
	if (panlist != NULL) {
	    panlist[1] = orig->list[1];
	    panlist[2] = 0;
	    for (i=3; i<=panlist[0]; i++) {
		panlist[i] = orig->list[i-1];
	    }
	    newlist = gretl_list_add(panlist, add, err);
	    free(panlist);
	}
    } else {
	newlist = gretl_list_add(orig->list, add, err);
    }

    return newlist;
}
