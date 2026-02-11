cpufreq_monitor_procfs_parse (CPUFreqMonitorProcfs *monitor,
			      gint                 *cpu,
			      gint                 *fmax,
			      gint                 *pmin,
			      gint                 *pmax,
			      gint                 *fmin,
			      gchar                *mode)
{
	gchar **lines;
	gchar  *buffer = NULL;
	gint    i, count;
	guint   mon_cpu;
	GError *error = NULL;

	if (!cpufreq_file_get_contents ("/proc/cpufreq", &buffer, NULL, &error)) {
		g_warning ("%s", error->message);
		g_error_free (error);

		return FALSE;
	}

	g_object_get (G_OBJECT (monitor),
		      "cpu", &mon_cpu, NULL);

	count = 0;
	lines = g_strsplit (buffer, "\n", -1);
	for (i = 0; lines[i]; i++) {
		if (g_ascii_strncasecmp (lines[i], "CPU", 3) == 0) {

			count = sscanf (lines[i], "CPU %d %d kHz (%d %%) - %d kHz (%d %%) - %20s",
					cpu, fmin, pmin, fmax, pmax, mode);

			if ((guint)(*cpu) == mon_cpu)
				break;
		}
	}

	g_strfreev (lines);
	g_free (buffer);

	return (count == 6);
}
