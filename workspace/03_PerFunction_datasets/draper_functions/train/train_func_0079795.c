cpufreq_monitor_procfs_run (CPUFreqMonitor *monitor)
{
	gint   fmax, fmin, cpu;
	gint   pmin, pmax;
	gchar  mode[21];
	gint   cur_freq, max_freq;
	gchar *governor;

	if (!cpufreq_monitor_procfs_parse (CPUFREQ_MONITOR_PROCFS (monitor),
					   &cpu, &fmax, &pmin, &pmax, &fmin, mode)) {


		if (!cpufreq_procfs_cpu_is_online ()) {
			g_object_set (G_OBJECT (monitor), "online", FALSE, NULL);
			return TRUE;
		}
		return FALSE;
	}

	governor = mode;
	max_freq = fmax;

	if (g_ascii_strcasecmp (governor, "powersave") == 0) {
		cur_freq = fmin;
	} else if (g_ascii_strcasecmp (governor, "performance") == 0) {
		cur_freq = fmax;
	} else if (g_ascii_strcasecmp (governor, "userspace") == 0) {
		cur_freq = cpufreq_monitor_procfs_get_freq_from_userspace (cpu);
	} else {
		cur_freq = fmax;
	}

	g_object_set (G_OBJECT (monitor),
		      "online", TRUE,
		      "governor", governor,
		      "frequency", cur_freq,
		      "max-frequency", max_freq,
		      NULL);

	return TRUE;
}
