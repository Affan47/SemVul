sigbus_handler_cb(int signum, siginfo_t *info, void *context)
{
	unsigned long pagesize = sysconf(_SC_PAGE_SIZE);
	DEBUG_1("SIGBUS %p", info->si_addr);
	mmap((void *)(((unsigned long)info->si_addr / pagesize) * pagesize), pagesize, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}
