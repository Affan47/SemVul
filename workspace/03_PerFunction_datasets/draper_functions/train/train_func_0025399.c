init_paths(CfgInfo *cfg)
{
	const gchar	*confdir;

	cfg->path.path[PTID_ICON]  = g_string_new(PATH_ICN);
	if((confdir = g_get_user_config_dir()) != NULL)
	{
		cfg->path.path[PTID_GTKRC] = g_string_new(confdir);
		g_string_append(cfg->path.path[PTID_GTKRC], G_DIR_SEPARATOR_S PACKAGE);
	}
	else
		cfg->path.path[PTID_GTKRC] = g_string_new(PATH_GRC);
	cfg->path.path[PTID_FSTAB] = g_string_new("/etc/fstab");
	cfg->path.path[PTID_MTAB]  = g_string_new("/proc/mounts");

	cfg->path.hideinfo.mode = HIDE_NONE;
	cfg->path.hideinfo.hide_re_src[0] = '\0';
	cfg->path.hideinfo.hide_re = NULL;
}
