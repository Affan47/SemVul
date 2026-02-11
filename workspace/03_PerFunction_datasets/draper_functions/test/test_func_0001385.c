load_module_dir (const char *dirname)
{
	GDir *dir;

	dir = g_dir_open (dirname, 0, NULL);

	if (dir) {
		const char *name;

		while ((name = g_dir_read_name (dir))) {
			if (g_str_has_suffix (name, "." G_MODULE_SUFFIX)) {
				char *filename;

				filename = g_build_filename (dirname,
							     name,
							     NULL);
				nautilus_module_load_file (filename);
				g_free (filename);
			}
		}

		g_dir_close (dir);
	}
}
