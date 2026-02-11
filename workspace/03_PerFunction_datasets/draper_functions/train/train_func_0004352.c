dup2(int oldfd, int newfd)
{
#define VT_IOWRAP_THISFUNCNAME dup2
	int ret;
	uint64_t enter_time;

	VT_IOWRAP_INIT_IOFUNC();

	VT_IOWRAP_CHECK_TRACING2(ret, oldfd, newfd);

	vt_cntl_msg(DBG_IO, stringify(VT_IOWRAP_THISFUNCNAME) ": %i, %i", oldfd, newfd);

	VT_IOWRAP_ENTER_IOFUNC();

	vt_cntl_msg(DBG_IO, "real_" stringify(VT_IOWRAP_THISFUNCNAME));
	VT_IOWRAP_CALL_LIBFUNC2(VT_IOWRAP_THISFUNCNAME, ret, oldfd, newfd);

	VT_IOWRAP_LEAVE_IOFUNC_DUP( ret!=newfd, oldfd, ret);

	return ret;
#undef VT_IOWRAP_THISFUNCNAME
}
