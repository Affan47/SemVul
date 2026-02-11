gtt_set_reports_menu (GnomeApp *app, GnomeUIInfo *new_menus)
{
	int i;
	char * path;


	path = g_strdup_printf ("%s/<Separator>", _("Reports"));


	if (reports_menu)
	{
		int nreports;
		for (i=0; GNOME_APP_UI_ENDOFINFO != reports_menu[i].type; i++) {}
		nreports = i;
		gnome_app_remove_menu_range (app, path, 1, nreports);

		if (new_menus != reports_menu)
		{
			for (i=0; i<nreports; i++)
			{


			}
			g_free (reports_menu);
		}
	}


	reports_menu = new_menus;
	if (!reports_menu)
	{
		reports_menu = g_new0 (GnomeUIInfo, 1);
		reports_menu[0].type = GNOME_APP_UI_ENDOFINFO;
	}


	for (i=0; GNOME_APP_UI_ENDOFINFO != reports_menu[i].type; i++)
	{
		reports_menu[i].moreinfo = invoke_report;
	}
	gnome_app_insert_menus (app, path, reports_menu);
}
