linginfo_lookup(const char *word, char **desc, char **stem)
{
	int res,i=0,bottom=0,top=lookuplen;
	while (top>=bottom) {
		if (i==(top-bottom)/2 + bottom) {
			return 0;
		}
		i=(top-bottom)/2 + bottom;
		if (hspell_debug) fprintf(stderr,"bot=%d i=%d top=%d) %s\n",bottom,i,top, lookup[i]);
		res = strcmp(lookup[i],word);
		if (res>0) {top=i;}
		else if (res<0) {bottom=i;}
		else {
			int len,desclen;
		        len = strlen(lookup[i]);
			*desc = lookup[i]+len+1;
			desclen = strlen(*desc);
			*stem = *desc+desclen+1;
			return 1;
		}
	}
	return 0;
}
