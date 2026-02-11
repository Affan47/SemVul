important(const char* format, ...) {
	va_list args; va_start(args, format);

	vprintf( format, args);
	printf( "\n");

	if(logfile) {
		vfprintf( logfile, format, args);
		fprintf( logfile, "\n");
	}
	va_end(args);
}
