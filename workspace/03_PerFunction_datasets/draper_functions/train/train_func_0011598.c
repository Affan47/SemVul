log_printf(int logfile_type, char *format, ...)
{
	char tmp[MAX_LOGFILE_LINE_LEN*4];
	va_list args;


	if(logfiles[logfile_type].log_file == NULL){
		return;
	}


	va_start(args, format);
	vsprintf(tmp, format, args);
	va_end(args);


	log_string(logfile_type, tmp);
}
