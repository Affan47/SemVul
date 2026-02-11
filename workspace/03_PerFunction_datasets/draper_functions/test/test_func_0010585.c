set_kerrno_with_trace(kerror_t errnum)
{
	if (!errnum)
		return;
	if (errnum < 0)
		errnum = -errnum;

	kerrno = errnum;
#ifdef __LINUX__
	void* return_addresses[2048];
	int naddr = backtrace(return_addresses,
		sizeof(return_addresses)/sizeof(void*));

	backtrace_symbols_fd(return_addresses, naddr, fileno(stderr));
	fflush(stderr);
#endif
}
