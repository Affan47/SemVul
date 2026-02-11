puts(const char *s)
{
#define VT_IOWRAP_THISFUNCNAME puts
	int ret;
	uint64_t enter_time;

	VT_IOWRAP_INIT_IOFUNC();

	VT_IOWRAP_CHECK_TRACING1(ret, s);

	vt_cntl_msg(DBG_IO, stringify(VT_IOWRAP_THISFUNCNAME) ": %p", s);

	VT_IOWRAP_ENTER_IOFUNC();

	vt_cntl_msg(DBG_IO, "real_" stringify(VT_IOWRAP_THISFUNCNAME));
	VT_IOWRAP_CALL_LIBFUNC1(VT_IOWRAP_THISFUNCNAME, ret, s);
	num_bytes = (ssize_t)strlen(s);

	VT_IOWRAP_LEAVE_IOFUNC( ret==EOF, fileno(stdout) );

	return ret;
#undef VT_IOWRAP_THISFUNCNAME
}
