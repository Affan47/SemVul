_get_sys_interface_freq_line(uint32_t cpu, char *filename,
					char * sbuf)
{
	int num_read, fd;
	FILE *sys_fp = NULL;
	char freq_file[80];
	char cpunfo_line [128];
	char cpufreq_line [10];

	if (cpunfo_frequency)

		return 1;

	snprintf(freq_file, 79,
		 "/sys/devices/system/cpu/cpu%d/cpufreq/%s",
		 cpu, filename);
	debug2("_get_sys_interface_freq_line: filename = %s ", freq_file);
	if ((sys_fp = fopen(freq_file, "r"))!= NULL) {

		fd = fileno(sys_fp);
		fcntl(fd, F_SETFD, FD_CLOEXEC);
		num_read = read(fd, sbuf, (sizeof(sbuf) - 1));
		if (num_read > 0) {
			sbuf[num_read] = '\0';
			debug2(" cpu %d freq= %s", cpu, sbuf);
		}
		fclose(sys_fp);
	} else {

		if (!cpunfo_frequency){
			snprintf(freq_file, 14, "/proc/cpuinfo");
			debug2("_get_sys_interface_freq_line: filename = %s ",
			       freq_file);
			if ((sys_fp = fopen(freq_file, "r")) != NULL) {
				while (fgets(cpunfo_line, sizeof cpunfo_line,
					     sys_fp) != NULL) {
					if (strstr(cpunfo_line, "cpu MHz") ||
					    strstr(cpunfo_line, "cpu GHz")) {
						break;
					}
				}
				strncpy(cpufreq_line, cpunfo_line+11, 8);
				_skipdot(cpufreq_line);
				sscanf(cpufreq_line, "%d", &cpunfo_frequency);
				debug2("cpunfo_frequency= %d",cpunfo_frequency);
				fclose(sys_fp);
			}
		}
		return 1;
	}
	return 0;
}
