read_key(FILE *fp,int *len) {
	unsigned char *buffer;
	unsigned char line[512];
	int size=0,index=0;
	if(!fp)
		return NULL;
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	buffer = (unsigned char *)malloc(size);
	memset(buffer,0,size);

	while(!feof(fp)) {
		memset(line,0,512);
		fgets(line,512,fp);
		if((line[0] == '-') || (line[0] == '\0'))
			continue;
		strncpy(buffer+index,line,strlen(line)-1);
		index = index+strlen(line)-1;
	}
	(*len) = index;
	return buffer;
}
