fputnflist(name, list, max, fp)
CONST char *name;
nftable list[];
u_int max;
FILE *fp;
{
	u_int n;
	int i;

	tblname[nfent] = name;
	tblent[nfent] = max;
	nfent++;

	qsort(list, max, sizeof(nftable), cmpnf);
	if (!textmode && fputword(max, fp) < 0) return(-1);
	if (fputbegin(name, fp) < 0) return(-1);
	for (n = 0; n < max; n++) {
		if (fputword(list[n].unicode, fp) < 0) return(-1);
		for (i = 0; i < MAXNFLEN; i++) {
			if (fputword(list[n].normalization[i], fp) < 0)
				return(-1);
		}
	}
	if (fputend(fp) < 0) return(-1);

	return(0);
}
