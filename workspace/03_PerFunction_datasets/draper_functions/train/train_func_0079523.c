refldbld(char *rec, char *fs)
{


	char *fr;
	void *p;
	int i, n;

	n = strlen(rec);
	if (n > fieldssize) {
		xfree(fields);
		if ((fields = (char *) malloc(n+1)) == NULL)
			FATAL("out of space for fields in refldbld %d", n);
		fieldssize = n;
	}
	fr = fields;
	*fr = '\0';
	if (*rec == '\0')
		return 0;
	p = compre(fs);
	   dprintf( ("into refldbld, rec = <%s>, pat = <%s>\n", rec, fs) );
	for (i = 1; ; i++) {
		if (i > nfields)
			growfldtab(i);
		if (freeable(fldtab[i]))
			xfree(fldtab[i]->sval);
		fldtab[i]->tval = FLD | STR | DONTFREE;
		fldtab[i]->sval = fr;
		   dprintf( ("refldbld: i=%d\n", i) );
		if (nematch(p, rec, rec)) {
			   dprintf( ("match %s (%d chars)\n", patbeg, patlen) );
			strncpy(fr, rec, patbeg-rec);
			fr += patbeg - rec + 1;
			*(fr-1) = '\0';
			rec = patbeg + patlen;
		} else {
			   dprintf( ("no match %s\n", rec) );
			strcpy(fr, rec);
			break;
		}
	}
	return i;
}
