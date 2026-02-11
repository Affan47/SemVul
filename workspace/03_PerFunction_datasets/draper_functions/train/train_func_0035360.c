output(LogLevel level, const char* tag, const char* func,
		const string& msg) throw ()
{
	fprintf(stderr, "%s %s: %.*s\n", tag, func, PFSTR(msg));
}
