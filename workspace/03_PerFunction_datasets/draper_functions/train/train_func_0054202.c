laggenr_from_to (int v, int minlag, int maxlag,
		      DATASET *dset, int *err)
{
    int *llist;
    int i, lv, nlags = -1;
    int p, reverse;

    if (maxlag < 0) {
	nlags = -maxlag + minlag + 1;
    } else if (maxlag > 0) {
	nlags = maxlag - minlag + 1;
    }

    if (nlags <= 0) {
	*err = E_DATA;
	return NULL;
    }

    llist = gretl_list_new(nlags);
    if (llist == NULL) {
	*err = E_ALLOC;
	return NULL;
    }

    reverse = (maxlag < minlag);
    p = minlag;

    for (i=0; i<nlags; i++) {
	lv = laggenr(v, p, dset);
	if (lv < 0) {
	    *err = E_DATA;
	    free(llist);
	    llist = NULL;
	    break;
	}
	llist[i+1] = lv;
	if (reverse) {
	    p--;
	} else {
	    p++;
	}
    }

    return llist;
}
