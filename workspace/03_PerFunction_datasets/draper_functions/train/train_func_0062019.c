read_config_files()   {

	gchar *filename;
	struct stat s;


	filename = g_strconcat(PACKAGE_DATA_DIR, "/default.conf", NULL);
	if(! parse_file_config(filename) ) {
		printf("Error opening config file %s\n",filename);
		exit(-1);
	}

	g_free(filename);


	filename = g_strconcat(global->path_home, "gtkatlantic.conf", NULL);
	if(stat(filename, &s) >= 0)
		parse_file_config(filename);

	g_free(filename);
}
