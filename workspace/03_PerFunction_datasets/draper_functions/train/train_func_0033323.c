format_av_pair(char* attr, char* val)
{
char	*buf;

    if ( *attr )
	buf = xmalloc(strlen(attr) + 1 + strlen(val) + 3, "format_av_pair(): 1");
    else
	buf = xmalloc(3, "format_av_pair(): 2");
    if ( !buf ) {
	my_xlog(OOPS_LOG_SEVERE, "format_av_pair(): No mem at send_av_pair.\n");
	return(NULL);
    }
    if ( *attr )
	sprintf(buf, "%s %s\r\n", attr, val);
    else
	sprintf(buf, "\r\n");
    return(buf);
}
