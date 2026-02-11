fsync(int fd)
{
#define VT_IOWRAP_THISFUNCNAME fsync
        int ret;
        uint64_t enter_time;

        VT_IOWRAP_INIT_IOFUNC();

        VT_IOWRAP_CHECK_TRACING1(ret, fd);

        vt_cntl_msg(DBG_IO, stringify(VT_IOWRAP_THISFUNCNAME) ": %i", fd);

        VT_IOWRAP_ENTER_IOFUNC();

        vt_cntl_msg(DBG_IO, "real_" stringify(VT_IOWRAP_THISFUNCNAME));
        VT_IOWRAP_CALL_LIBFUNC1(VT_IOWRAP_THISFUNCNAME, ret, fd);

        VT_IOWRAP_LEAVE_IOFUNC( ret==-1, fd);

        return ret;
#undef VT_IOWRAP_THISFUNCNAME
}
