fat16_getFreeCluster(Volume_t *V) {
	DWORD c, val;
	int res;
	if (V->freecnt <= 0) { fprintf(stderr,"getFreeCluster: end of free clusters in the volume\n"); return 0; }

	do {
		val = V->nextfree;
		if ((res = fat_read_entry(V, V->nextfree++, 0, &c)) < 0) { fprintf(stderr,"getFreeCluster16 error\n"); return 0; }
		if ( V->nextfree > (V->DataClusters + 1))  V->nextfree = 2;
		if (fat_isfree(V,c)) { V->freecnt--; return val; }
	} while (V->freecnt > 0);

	fprintf(stderr,"getFreeCluster: end of free clusters in the volume\n");
	return 0;
}
