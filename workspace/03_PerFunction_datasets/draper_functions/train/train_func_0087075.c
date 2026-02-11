make_op_list (const int *list, DATASET *dset,
			  int **pdumlist, int *err)
{
    int *dumlist;
    int *biglist;
    int i, k, nv;

    dumlist = make_dummies_list(list, dset, err);
    if (dumlist == NULL) {
	return NULL;
    }

    nv = list[0] + dumlist[0];

    biglist = gretl_list_new(nv);
    if (biglist == NULL) {
	free(dumlist);
	*err = E_ALLOC;
	return NULL;
    }

    k = 1;
    for (i=1; i<=list[0]; i++) {
	biglist[k++] = list[i];
    }
    for (i=1; i<=dumlist[0]; i++) {
	biglist[k++] = dumlist[i];
    }

    *pdumlist = dumlist;

    return biglist;
}
