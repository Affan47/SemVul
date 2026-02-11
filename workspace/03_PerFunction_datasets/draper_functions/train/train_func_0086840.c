intelhex_fileopen (inteldata *id, char *filename, int mode) {


    if (mode==0) {
	id->file=fopen(filename,"w");
	if (id->file==NULL) {
	    fprintf(stderr,"File create error\n");
	    abort(); }
        id->eof_found=0;
        return 1;
    }
    id->file=fopen(filename,"r");
    if (id->file==NULL) {
	fprintf(stderr,"Error when opening the file '%s' for reading.\n",filename);
	abort(); }
    id->eof_found=0;
    return 1;
}
