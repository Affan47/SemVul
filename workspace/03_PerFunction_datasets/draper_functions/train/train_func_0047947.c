_read_msr(int fd, int which)
{
	uint64_t data = 0;
	static bool first = true;

	if (lseek(fd, which, SEEK_SET) < 0)
		error("lseek of /dev/cpu/#/msr: %m");
	if (read(fd, &data, sizeof(data)) != sizeof(data)) {
		if (which == MSR_DRAM_ENERGY_STATUS) {
			if (first && (debug_flags & DEBUG_FLAG_ENERGY)) {
				first = false;
				info("It appears you don't have any DRAM, "
				     "this can be common.  Check your system "
				     "if you think this is in error.");
			}
		} else {
			debug("Check if your CPU has RAPL support for %s: %m",
			      _msr_string(which));
		}
	}
	return data;
}
