gretl_list_omit_last (const int *orig, int *err)
{
    int *list = NULL;
    int i;

    *err = 0;

    if (orig[0] < 2) {
	*err = E_NOVARS;
    } else {
	for (i=1; i<=orig[0]; i++) {
	    if (orig[i] == LISTSEP) {

		*err = 1;
		break;
	    }
	}
    }

    if (!*err) {
	list = gretl_list_new(orig[0] - 1);
	if (list == NULL) {
	    *err = E_ALLOC;
	} else {
	    for (i=1; i<orig[0]; i++) {
		list[i] = orig[i];
	    }
	}
    }

    return list;
}
