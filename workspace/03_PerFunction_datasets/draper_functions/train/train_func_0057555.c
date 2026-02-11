hbfile_setup(gboolean file_clear)
{

	DB( g_print("\n[hbfile] setup\n") );
	DB( g_print("- file clear is %d\n", file_clear) );


	da_acc_new();
	da_pay_new();
	da_cat_new();
	da_tag_new();
	da_asg_new();

	GLOBALS->h_memo = g_hash_table_new_full(g_str_hash, g_str_equal, (GDestroyNotify)g_free, NULL);
	GLOBALS->arc_list = NULL;
	GLOBALS->ope_list = NULL;


	if(file_clear == TRUE)
	{

		hbfile_change_filepath(g_build_filename(PREFS->path_hbfile, "untitled.xhb", NULL));
		GLOBALS->hbfile_is_new = TRUE;

		DB( g_print("- path_hbfile is '%s'\n", PREFS->path_hbfile) );
		DB( g_print("- xhb_filepath is '%s'\n", GLOBALS->xhb_filepath) );
	}
	else
	{
		GLOBALS->hbfile_is_new = FALSE;
	}

	hbfile_change_owner(g_strdup(_("Unknown")));


	GLOBALS->vehicle_category = 0;

	GLOBALS->auto_nbdays = 0;
	GLOBALS->auto_weekday = 1;
	GLOBALS->auto_smode = 0;

	GLOBALS->changes_count = 0;

	GLOBALS->xhb_hasbak = FALSE;

}
