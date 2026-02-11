make_dollar_list (DATASET *dset, int *err)
{
    int *list = NULL;
    int i;

    for (i=1; i<dset->v; i++) {
	if (dset->varname[i][0] == '$') {
	    list = gretl_list_append_term(&list, i);
	    if (list == NULL) {
		*err = E_ALLOC;
		break;
	    }
	}
    }

    return list;
}
