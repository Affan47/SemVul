RTMP_LogStatus(const char *format, ...)
{
	char str[MAX_PRINT_LEN]="";
	va_list args;
	va_start(args, format);
	vsnprintf(str, MAX_PRINT_LEN-1, format, args);
	va_end(args);

	if ( RTMP_debuglevel==RTMP_LOGCRIT )
		return;

	if ( !fmsg ) fmsg = stderr;

	fprintf(fmsg, "%s", str);
	fflush(fmsg);
	neednl = 1;
}
