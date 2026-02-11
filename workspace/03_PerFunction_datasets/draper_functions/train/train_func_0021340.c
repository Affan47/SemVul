formdata(char *p)
{
    char *pp;
    int inlen;
    char *ctype;
    inlen=0; ctype=getenv("CONTENT_TYPE");
    if(ctype==NULL || strstr(ctype,"multipart/form-data")==NULL
       || (p=strstr(ctype,"boundary="))==NULL) {
	bad: stdinbuf=""; return 0;
    }
    pp=getenv("CONTENT_LENGTH");
    if(pp==NULL) goto bad;
    inlen=atoi(pp); if(inlen<=10) goto bad;
    if(inlen>=MAX_DEPOSITLEN) user_error("parm_too_long");
    stdinbuf=xmalloc(inlen+1); readstdin(inlen);
    p+=strlen("boundary=");
    for(pp=p;myisalnum(*pp) || *pp=='-'; pp++);
    if(pp-p<sizeof(mpboundary)-2) {
	memmove(mpboundary,p,pp-p); mpboundary[pp-p]=0;
    }

    if(strstr(stdinbuf,mpboundary)==NULL || strstr(stdinbuf,"name=")==NULL) {
	free(stdinbuf); goto bad;
    }
    form_access=1; post_log();
    return inlen;
}
