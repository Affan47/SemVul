perror(const char *format, ...)
{
    if (level >= ERROR)
    {   char * buf = new char[strlen(format) + 5];
	(void) strcpy(buf, format);
	(void) strcat(buf, ": %m");
	va_list args;
	va_start(args, format);
	vlog(ERROR, buf, args);
	va_end(args);
        delete[] buf;
    }
}
