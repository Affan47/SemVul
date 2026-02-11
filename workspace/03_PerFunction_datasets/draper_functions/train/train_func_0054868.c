compress_daily (DATASET *dset, int pd)
{
    int t, yr, mon, day;

    for (t=0; t<dset->n; t++) {
	sscanf(dset->S[t], YMD_READ_FMT, &yr, &mon, &day);
	if (pd == 1) {
	    sprintf(dset->S[t], "%d", yr);
	} else if (pd == 12) {
	    sprintf(dset->S[t], "%d:%02d", yr, mon);
	} else if (pd == 4) {
	    sprintf(dset->S[t], "%d:%d", yr, mon / 3 + (mon % 3 != 0));
	}
    }

    return 0;
}
