getWcharCp(void) {
	unsigned int i;
	if(wcharCp != NULL)
		return wcharCp;
	for(i=0; i< sizeof(wcharTries) / sizeof(wcharTries[0]); i++) {
		if(try(wcharTries[i]))
			return (wcharCp=wcharTries[i]);
	}
	fprintf(stderr, "No codepage found for wchar_t\n");
	return NULL;
}
