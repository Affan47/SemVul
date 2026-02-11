ajMessErrorSetFile(const char *errfile)
{
    FILE *fp = 0;

    if(errfile)
	if((fp = fopen(errfile,"r")))
	{
	    messErrorFile = ajSysFuncStrdup(errfile);
	    fclose(fp);

	    return ajTrue;
	}

    return ajFalse;
}
