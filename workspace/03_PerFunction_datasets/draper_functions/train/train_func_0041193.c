describe_rlimit_res_t(__rlimit_resource_t rlim)
{
	switch (rlim)
	{
		case RLIMIT_CPU: return "CPU time in seconds";
		case RLIMIT_FSIZE: return "Maximum filesize";
		case RLIMIT_DATA: return "max data size";
		case RLIMIT_STACK: return "max stack size";
		case RLIMIT_CORE: return "max core file size";
		case RLIMIT_RSS: return "max resident set size";
		case RLIMIT_NPROC: return "max number of processes";
		case RLIMIT_NOFILE: return "max number of open files";
		case RLIMIT_MEMLOCK: return "max locked-in-memory address spac";
		case RLIMIT_AS: return "address space (virtual memory) limit";
		default: return "unknown";
	}
}
