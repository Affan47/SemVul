fontset_transsep(char *nfname, char *ofname, int n)
{
    char *s;

    strncpy(nfname, ofname, n);
    if (nfname[n-1]!='\0')
	nfname[n]='\0';
    if (strchr(nfname, ','))
	return 1;
    s = nfname;
    while ((s = strchr(nfname, FontSetSep)) != NULL){
	*s = ',';
	nfname = s;
    }
    return 0;
}
