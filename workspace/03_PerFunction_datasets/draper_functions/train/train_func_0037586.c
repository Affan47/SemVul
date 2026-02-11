gtt_save_reports_menu (void)
{
	int i;
	char s[120], *p;
	GnomeUIInfo * reports_menu;
	GConfClient *client;

	client = gconf_client_get_default ();
	reports_menu = gtt_get_reports_menu();


	for (i=0; GNOME_APP_UI_ENDOFINFO != reports_menu[i].type; i++)
	{
		GttPlugin *plg = reports_menu[i].user_data;
	   g_snprintf(s, sizeof (s), GTT_GCONF"/Reports/%d/", i);
		p = s + strlen(s);
	   strcpy (p, "Name");
		F_SETSTR (s, plg->name);

	   strcpy (p, "Path");
		F_SETSTR (s, plg->path);

	   strcpy (p, "Tooltip");
		F_SETSTR (s, plg->tooltip);

	   strcpy (p, "LastSaveURL");
		F_SETSTR (s, plg->last_url);

	   *p = 0;
		gtt_save_gnomeui_to_gconf (client, s, &reports_menu[i]);
	}
	SETINT ("/Misc/NumReports", i);
}
