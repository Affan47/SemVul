get_starting_length (const int *list, DATASET *dset, int trim)
{
    int width = VNAMELEN - 3 - trim;
    const char *vni, *vnj;
    int len, maxlen = 0;
    int conflict = 0;
    int i, j;

    if (list[0] == 1) {
	return VNAMELEN - 1;
    }

    for (i=1; i<=list[0]; i++) {
	len = strlen(dset->varname[list[i]]);
	if (len > maxlen) {
	    maxlen = len;
	}
    }

    if (maxlen <= width) {

	return VNAMELEN - 3;
    }

    for (len=width; len<=maxlen; len++) {
	conflict = 0;
	for (i=1; i<=list[0] && !conflict; i++) {
	    vni = dset->varname[list[i]];
	    for (j=i+1; j<=list[0] && !conflict; j++) {
		vnj = dset->varname[list[j]];
		if (!strncmp(vni, vnj, len)) {
		    conflict = 1;
		}
	    }
	}
	if (!conflict) {
	    break;
	}
    }

    len += trim;

    if (len < VNAMELEN - 3) {
	len = VNAMELEN - 3;
    } else if (len > VNAMELEN - 1) {
	len = VNAMELEN - 1;
    }

    return len;
}
