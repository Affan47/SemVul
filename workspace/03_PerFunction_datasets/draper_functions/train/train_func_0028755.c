open_process_map (int pid, const char *mode)
{
	FILE *fp = NULL;
	const gchar *proc_path[] = {
		"/proc/%d/maps",
		"/proc/%d/map",
		NULL
	};
	int i;
	gchar *filename;

	for (i = 0; fp == NULL && proc_path [i]; i++) {
 		filename = g_strdup_printf (proc_path[i], pid);
		fp = fopen (filename, mode);
		g_free (filename);
	}

	return fp;
}
