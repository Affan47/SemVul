oc_logopen(const char* file)
{
    if(!ocloginit) oc_loginit();
    if(oclogfile != NULL) {
	fclose(oclogstream);
	free(oclogfile);
	oclogfile = NULL;
    }
    if(file == NULL || strlen(file) == 0) {

	oclogstream = stderr;
	oclogfile = NULL;
    } else {
	int fd;
	oclogfile = (char*)malloc(strlen(file)+1);
	strcpy(oclogfile,file);
	oclogstream = NULL;


	fd = open(oclogfile,O_WRONLY|O_APPEND|O_CREAT,0600);
	if(fd >= 0) {
	    oclogstream = fdopen(fd,"a");
	} else {
	    free(oclogfile);
	    oclogfile = NULL;
	    oc_setlogging(0);
	}
    }
}
