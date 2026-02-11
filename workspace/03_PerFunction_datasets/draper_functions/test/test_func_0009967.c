dumpdosdrive(flaglist, origflaglist, fp)
CONST char *flaglist;
char *origflaglist;
XFILE *fp;
{
	char *new;
	int i, j, n;

	if (origflaglist || origmaxfdtype <= 0) new = NULL;
	else {
		origflaglist = new = Xmalloc(origmaxfdtype * sizeof(char));
		memset(origflaglist, 0, origmaxfdtype * sizeof(char));
	}

	for (i = n = 0; i < maxfdtype; i++) {
		if (flaglist && flaglist[i]) continue;
		j = searchdrv(&(fdtype[i]), origfdtype, origmaxfdtype, 1);
		if (j < origmaxfdtype) {
			origflaglist[j] = 1;
			continue;
		}
		n++;
#  ifdef	HDDMOUNT
		if (fdtype[i].cyl) continue;
		for (; i + 1 < maxfdtype; i++) {
			if (fdtype[i + 1].cyl
			|| fdtype[i + 1].drive != fdtype[i].drive + 1
			|| strpathcmp(fdtype[i + 1].name, fdtype[i].name))
				break;
		}
#  endif
	}
	for (i = 0; i < origmaxfdtype; i++) {
		if (origflaglist[i]) continue;
		n++;
	}

	if (!n || !fp) {
		Xfree(new);
		return(n);
	}

	VOID_C fputnl(fp);
	Xfputs("# MS-DOS drive definition\n", fp);
	for (i = 0; i < maxfdtype; i++) {
		if (flaglist && flaglist[i]) continue;
		j = searchdrv(&(fdtype[i]), origfdtype, origmaxfdtype, 1);
		if (j < origmaxfdtype) continue;
		printsetdrv(fdtype, i, 1, 0, fp);
#  ifdef	HDDMOUNT
		if (fdtype[i].cyl) continue;
		for (; i + 1 < maxfdtype; i++) {
			if (fdtype[i + 1].cyl
			|| fdtype[i + 1].drive != fdtype[i].drive + 1
			|| strpathcmp(fdtype[i + 1].name, fdtype[i].name))
				break;
		}
#  endif
	}
	for (i = 0; i < origmaxfdtype; i++) {
		if (origflaglist[i]) continue;
		printsetdrv(origfdtype, i, 0, 0, fp);
	}
	Xfree(new);

	return(n);
}
