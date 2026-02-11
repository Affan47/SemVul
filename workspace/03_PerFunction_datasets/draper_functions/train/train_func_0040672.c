HasResourceFork(char *filename) {


    char *respath = malloc(strlen(filename)+strlen("/rsrc")+1);
    FILE *temp;
    int ret = false;

    strcpy(respath,filename);
    strcat(respath,"/rsrc");
    temp = fopen(respath,"r");
    free(respath);
    if ( temp!=NULL )
	ret = IsResourceFork(temp,0);
return( ret );
}
