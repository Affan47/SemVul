main (int argc, char **argv)
{
	GDir *dir;
	const char *name;

	setlocale (LC_ALL, "");
	bind_textdomain_codeset ("libc", "UTF-8");

	if (argv[1] != NULL) {
		verbose = 1;

		if (g_str_equal (argv[1], "-c"))
			print_endianess (NULL);
		else
			print_endianess (argv[1]);
		return 0;
	}

	dir = g_dir_open ("/usr/share/i18n/locales/", 0, NULL);
	if (dir == NULL) {


		dir = g_dir_open ("/usr/share/locale/", 0, NULL);
		if (dir == NULL) {
			return 1;
		}
	}

	while ((name = g_dir_read_name (dir)) != NULL)
		print_endianess (name);

	return 0;
}
