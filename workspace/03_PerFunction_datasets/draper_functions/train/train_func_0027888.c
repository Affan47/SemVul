get_data_dir(){
	static gchar* data_dir=NULL;
	if (data_dir) return data_dir;

	GList *paths=NULL, *i=NULL;
	gchar *tmp;

	i=g_list_append(i, (gchar*)"share");
	paths=i;

	i=g_list_append(i, (gchar*)g_get_user_data_dir());

	const gchar* const *datadirs = g_get_system_data_dirs();
	for (gint datadirs_i=0; datadirs[datadirs_i];++datadirs_i){
		i=g_list_append(i, (gchar*)datadirs[datadirs_i]);
	}

	i=paths;
	GStatBuf sb;
	while (i){
		tmp = g_build_filename((gchar*)i->data, "gpick", NULL);

		if (g_stat( tmp, &sb )==0){
			data_dir=g_strdup(tmp);
			g_free(tmp);
			break;
		}
		g_free(tmp);
		i=g_list_next(i);
	}

	g_list_free(paths);

	if (data_dir==NULL){
		data_dir=g_strdup("");
		return data_dir;
	}

	return data_dir;
}
