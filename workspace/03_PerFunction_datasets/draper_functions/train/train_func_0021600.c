open_compressed(char *dictname){
	FILE *fp;
	char command_string[100];
	int namelen;
	int extlen;

	if(access(dictname,R_OK)!= 0){
		return NULL;
	}

#ifdef UNCOMPRESS
	namelen = strlen(dictname);
	extlen = strlen(UNCOMPRESSEXT);
	if(strncmp(&dictname[namelen-extlen],UNCOMPRESSEXT,extlen) != 0 ){
		namelen = 0;
		fp = fopen(dictname,"r");
	} else {
		sprintf(command_string,"%s %s",UNCOMPRESS,dictname);
		fp = (FILE *) popen(command_string,"r");
	}
#else
	fp = fopen(dictname,"r");
#endif
	if(fp == NULL){
		perror("Cannot open translation file");
		fprintf(stderr,"We were attempting to open %s\n",dictname);
#ifdef UNCOMPRESS
		if(namelen >0)
			fprintf(stderr,"Using uncompression method \"%s\"\n",
				UNCOMPRESS);
#endif
		return NULL;
	}
	return fp;

}
