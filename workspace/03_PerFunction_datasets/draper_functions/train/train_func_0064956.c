fputs(const char *s, FILE *stream)
{
#define VT_IOWRAP_THISFUNCNAME fputs
	int ret;
	uint64_t enter_time;
        int tmp;

	VT_IOWRAP_INIT_IOFUNC();

	VT_IOWRAP_CHECK_TRACING2(ret, s, stream);

	vt_cntl_msg(DBG_IO, stringify(VT_IOWRAP_THISFUNCNAME) ": %i, %p",
		stream != NULL ? fileno(stream) : -1, s);

	VT_IOWRAP_ENTER_IOFUNC();

	vt_cntl_msg(DBG_IO, "real_" stringify(VT_IOWRAP_THISFUNCNAME));
	VT_IOWRAP_CALL_LIBFUNC2(VT_IOWRAP_THISFUNCNAME, ret, s, stream);
	num_bytes = (ssize_t)strlen(s);
        tmp=(stream!=NULL) ? fileno(stream): 0;

	VT_IOWRAP_LEAVE_IOFUNC( ret==EOF, tmp );

	return ret;
#undef VT_IOWRAP_THISFUNCNAME
}
