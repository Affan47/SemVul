build_load_menu_grp(GKeyFile *config, GeanyBuildCommand **dst, gint grp,
								gchar *prefix, gboolean loc)
{
	guint cmd;
	gsize prefixlen;
	GeanyBuildCommand *dstcmd;
	gchar *key;
	static gchar cmdbuf[3] = "  ";

	if (*dst == NULL)
		*dst = g_new0(GeanyBuildCommand, build_groups_count[grp]);
	dstcmd = *dst;
	prefixlen = prefix == NULL ? 0 : strlen(prefix);
	key = g_strconcat(prefix == NULL ? "" : prefix, fixedkey, NULL);
	for (cmd = 0; cmd < build_groups_count[grp]; ++cmd)
	{
		gchar *label;
		if (cmd >= 100)
			return;
		sprintf(cmdbuf, "%02d", cmd);
		set_key_grp(key, groups[grp]);
		set_key_cmd(key, cmdbuf);
		set_key_fld(key, "LB");
		if (loc)
			label = g_key_file_get_locale_string(config, build_grp_name, key, NULL, NULL);
		else
			label = g_key_file_get_string(config, build_grp_name, key, NULL);
		if (label != NULL)
		{
			dstcmd[cmd].exists = TRUE;
			SETPTR(dstcmd[cmd].label, label);
			set_key_fld(key,"CM");
			SETPTR(dstcmd[cmd].command,
					g_key_file_get_string(config, build_grp_name, key, NULL));
			set_key_fld(key,"WD");
			SETPTR(dstcmd[cmd].working_dir,
					g_key_file_get_string(config, build_grp_name, key, NULL));
		}
		else dstcmd[cmd].exists = FALSE;
	}
	g_free(key);
}
