write(int fd, const void *buf, size_t count)
{
#define VT_IOWRAP_THISFUNCNAME write
	ssize_t ret;
	uint64_t enter_time;

	VT_IOWRAP_INIT_IOFUNC();

	VT_IOWRAP_CHECK_TRACING3(ret, fd, buf, count);

	vt_cntl_msg(DBG_IO, stringify(VT_IOWRAP_THISFUNCNAME) ": %i, %zu", fd, count);

	VT_IOWRAP_ENTER_IOFUNC();

	vt_cntl_msg(DBG_IO, "real_" stringify(VT_IOWRAP_THISFUNCNAME));
	VT_IOWRAP_CALL_LIBFUNC3(VT_IOWRAP_THISFUNCNAME, ret, fd, buf, count);
	num_bytes = ret;

	VT_IOWRAP_LEAVE_IOFUNC( ret==-1, fd);

	return ret;
#undef VT_IOWRAP_THISFUNCNAME
}
