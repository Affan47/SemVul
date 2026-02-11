buildname(char *basedir,char *sub) {
    char *fname = galloc(strlen(basedir)+strlen(sub)+2);

    strcpy(fname, basedir);
    if ( fname[strlen(fname)-1]!='/' )
	strcat(fname,"/");
    strcat(fname,sub);
return( fname );
}
