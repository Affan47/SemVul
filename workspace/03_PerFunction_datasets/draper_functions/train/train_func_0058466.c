GV_get_vect_list(int *numvects)
{
    int i, *ret;

    *numvects = Next_vect;

    if (Next_vect) {
	ret = (int *)G_malloc(Next_vect * sizeof(int));
	if (!ret) {
	    return (NULL);
	}

	for (i = 0; i < Next_vect; i++) {
	    ret[i] = Vect_ID[i];
	}

	return (ret);
    }

    return (NULL);
}
