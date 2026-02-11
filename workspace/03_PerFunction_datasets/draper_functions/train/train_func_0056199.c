bail(char *progname,char *msg,...) {
    int n;
    va_list ap;
    int e=errno;
    va_start(ap, msg);
    fprintf(log_fp,";;; %s: %ld: FATAL ",progname,time(0));
    n=vfprintf(log_fp,msg,ap);
    va_end(ap);
    if(e>0)
	fprintf(log_fp," (%s)\n",strerror(e));
    else
	fputc('\n',log_fp);

    kill(getpid(),15);

}
