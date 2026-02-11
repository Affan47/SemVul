paramcheck34(NCDAPCOMMON* nccomm, const char* param, const char* substring)
{
    const char* value;
    const char* sh;
    unsigned int splen;
    if(nccomm == NULL || param == NULL) return 0;
    value = oc_clientparam_get(nccomm->oc.conn,param);
    if(value == NULL) return 0;
    if(substring == NULL) return 1;
    splen = strlen(substring);
    for(sh=value;*sh;sh++) {
	if(strncmp(sh,substring,splen)==0) {
	    char cpost = sh[splen];
	    char cpre;
	    int match = 0;
	    cpre = (sh==value?*sh:*(sh-1));

	    if(sh == value || strchr(checkseps,cpre) != NULL) match++;
	    if(cpost == '\0' || strchr(checkseps,cpost) != NULL) match++;
	    if(match == 2) return 1;
	}
    }
    return 0;
}
