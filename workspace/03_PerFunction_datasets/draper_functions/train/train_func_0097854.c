cb_gnm_option_group_post_parse (GOptionContext *context,
				GOptionGroup   *group,
				gpointer        data,
				GError        **error)
{
	if (param_show_version) {
		g_print (_("gnumeric version '%s'\ndatadir := '%s'\nlibdir := '%s'\n"),
			 GNM_VERSION_FULL, gnm_sys_data_dir (), gnm_sys_lib_dir ());
		exit (0);
	}
	return TRUE;
}
