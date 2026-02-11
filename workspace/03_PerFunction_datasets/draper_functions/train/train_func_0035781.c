_is_power_cpu(void)
{
	if (is_power == -1) {
		FILE *cpu_info_file;
		char buffer[128];
		char* _cpuinfo_path = "/proc/cpuinfo";
		cpu_info_file = fopen(_cpuinfo_path, "r");
		if (cpu_info_file == NULL) {
			error("_get_is_power: error %d opening %s", errno,
			      _cpuinfo_path);
			return false;
		}

		is_power = 0;
		while (fgets(buffer, sizeof(buffer), cpu_info_file) != NULL) {
			if (strstr(buffer, "POWER7")) {
				is_power = 1;
				break;
			}
		}
		fclose(cpu_info_file);
	}

	if (is_power == 1)
		return true;
	return false;
}
