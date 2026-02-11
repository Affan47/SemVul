homebank_check_app_dir()
{
gchar *homedir;
const gchar *configdir;
gboolean exists;

	DB( g_print("\n[homebank] check_app_dir\n") );


#ifndef G_OS_WIN32
	configdir = g_get_user_config_dir();
	DB( g_print("- check '%s' exists\n", configdir) );
	if(!g_file_test(configdir, G_FILE_TEST_IS_DIR))
	{
		DB( g_print("- creating dir\n") );
		g_mkdir(configdir, 0755);
	}
#endif


	configdir = homebank_app_get_config_dir();
	DB( g_print("- config_dir is: '%s'\n", configdir) );
	exists = g_file_test(configdir, G_FILE_TEST_IS_DIR);
	if(exists)
	{

		DB( g_print("- chmod 0700\n") );
		g_chmod(configdir, 0700);
		GLOBALS->first_run = FALSE;
	}
	else
	{

		DB( g_print("- create config_dir\n") );
		g_mkdir(configdir, 0755);
		g_chmod(configdir, 0700);


		homedir = g_build_filename(g_get_home_dir (), ".homebank", NULL );
		DB(	g_print("- homedir is: '%s'\n", homedir) );

		exists = g_file_test(homedir, G_FILE_TEST_IS_DIR);
		if(exists)
		{
		gboolean f1, f2;

			DB( g_print("- migrate old 2 files\n") );
			f1 = homebank_check_app_dir_migrate_file(homedir, config_dir, "preferences");
			f2 = homebank_check_app_dir_migrate_file(homedir, config_dir, "lastopenedfiles");
			if(f1 && f2)
			{
				DB( g_print("- removing old dir\n") );
				g_rmdir(homedir);
			}
		}
		g_free(homedir);
		GLOBALS->first_run = TRUE;
	}

}
