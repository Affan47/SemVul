GDrawIError(const char *fmt,...) {
    char buf[1025]; unichar_t ubuf[1025];
    va_list ap;

    strcpy(buf,"Internal Error:\n");
    va_start(ap, fmt);
    vsprintf(buf+strlen(buf), fmt, ap);
    va_end(ap);
    fprintf( stderr, "%s\n", buf );
    _GDraw_InitError(NULL);
    if ( error!=NULL ) {
	ProcessText(ubuf,buf,et_error);
	RunError();
    }
}
