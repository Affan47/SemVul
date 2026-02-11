cpu_freq_send_info(int fd)
{
	if (cpu_freq_count) {
		safe_write(fd, &cpu_freq_count, sizeof(uint16_t));
		safe_write(fd, cpufreq,
			   (cpu_freq_count * sizeof(struct cpu_freq_data)));
	} else {
		safe_write(fd, &cpu_freq_count, sizeof(uint16_t));
	}
	return;
rwfail:
	error("Unable to send cpu frequency information for %u cpus",
	      cpu_freq_count);
	return;
}
