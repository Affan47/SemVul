open_file(char *fstring,char *subfile,char *cmnd)
{
	FILE	*fptr;
	char	s[100];

	while(fstring[0] == ' ') fstring++;
	strcpy(s,fstring);
	strcat(s,subfile);
	if((fptr = fopen(s,cmnd)) == NULL) {
		fprintf(stderr,"Could not open file \"%s\"\n",s);
		print_error("File does not exist!\n");
	}
	return(fptr);
}
