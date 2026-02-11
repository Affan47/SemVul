NCstringReplace(char **input, int s, int e, char *newstr) {
	int i,j;
	char *ret;
	if(e < s) { CMmsgPrint (CMmsgUsrError, "NCstringReplace(): end is less than start!\n"); abort(); }
	if((ret = malloc(sizeof(char) * ((strlen(*input) - (e - s)) + strlen(newstr) + 1))) == (char *) NULL)
		{ CMmsgPrint (CMmsgSysError, "Memory allocation error in: %s %d",__FILE__,__LINE__); return NCfailed; }
	for (i = 0,j = 0; j < s; i++,j++) ret[i] = (*input)[j];
	s = strlen(newstr);
	for (j = 0; j < s; i++,j++) ret[i] = newstr[j];
	s = strlen(*input);
	for (j = e; j < s; i++,j++) ret[i] = (*input)[j];
	ret[i] = '\0';
	free(*input);
	*input = ret;
	return NCsucceeded;
}
