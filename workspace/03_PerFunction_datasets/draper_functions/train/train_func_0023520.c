on_combobox1_changed                   (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
	GSList	*list;
	gchar *reponame_combo;
	GError **error = NULL;
	gboolean success = FALSE;
	static gboolean first_run = TRUE;


	reponame_combo = gtk_combo_box_get_active_text(combobox);

	global_curr_reponame = g_strdup(reponame_combo);


	if(!global_curr_reponame)
	{
		global_curr_reponame = g_strdup("OSM");
		printf("YOUR DISTRIBUTION SUCKS BIGTIME\n");
	}


	for(list = global_repo_list; list != NULL; list = list->next)
	{
		repo_t	*repo;
		gchar	*reponame;

		repo = list->data;
		reponame = g_strdup(repo->name);

		if(	g_strrstr(reponame,global_curr_reponame) != NULL &&
			strlen(reponame) == strlen(global_curr_reponame)
		)
		{
			global_curr_repo = list;
		}
	}


	success = gconf_client_set_string(
					global_gconfclient,
					GCONF"/repo_name",
					global_curr_reponame,
					error);

	global_repo_nr = gtk_combo_box_get_active(combobox);


	if(first_run) {
		first_run = FALSE;
	}
	else
		repaint_all();
}
