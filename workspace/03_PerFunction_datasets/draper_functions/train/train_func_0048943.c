ioManagerWakeup (void)
{
    int r;

    if (io_manager_wakeup_fd >= 0) {
#if defined(HAVE_EVENTFD)
	StgWord64 n = (StgWord64)IO_MANAGER_WAKEUP;
	r = write(io_manager_wakeup_fd, (char *) &n, 8);
#else
	StgWord8 byte = (StgWord8)IO_MANAGER_WAKEUP;
	r = write(io_manager_wakeup_fd, &byte, 1);
#endif
        if (r == -1) { sysErrorBelch("ioManagerWakeup: write"); }
    }
}
