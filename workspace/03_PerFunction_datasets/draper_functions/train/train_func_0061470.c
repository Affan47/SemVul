brasero_project_manager_init (BraseroProjectManager *obj)
{
	GtkWidget *type;
	GtkAction *action;
	GtkWidget *chooser;

	obj->priv = g_new0 (BraseroProjectManagerPrivate, 1);

	gtk_notebook_set_show_border (GTK_NOTEBOOK (obj), FALSE);
	gtk_notebook_set_show_tabs (GTK_NOTEBOOK (obj), FALSE);

	obj->priv->action_group = gtk_action_group_new ("ProjectManagerAction");
	gtk_action_group_set_translation_domain (obj->priv->action_group, GETTEXT_PACKAGE);
	gtk_action_group_add_actions (obj->priv->action_group,
				      entries,
				      G_N_ELEMENTS (entries),
				      obj);

	action = gtk_action_group_get_action (obj->priv->action_group, "NewChoose");
	g_object_set (action,
		      "short-label", _("_New"),
		      NULL);
	action = gtk_action_group_get_action (obj->priv->action_group, "Open");
	g_object_set (action,
		      "short-label", _("_Open"),
		      NULL);


	type = brasero_project_type_chooser_new ();
	gtk_widget_show (type);
	g_signal_connect (type,
			  "chosen",
			  G_CALLBACK (brasero_project_manager_type_changed_cb),
			  obj);
	g_signal_connect (type,
			  "recent-clicked",
			  G_CALLBACK (brasero_project_manager_recent_clicked_cb),
			  obj);
	g_signal_connect (type,
			  "last-saved",
			  G_CALLBACK (brasero_project_manager_last_saved_clicked_cb),
			  obj);
	gtk_notebook_prepend_page (GTK_NOTEBOOK (obj), type, NULL);


	obj->priv->layout = brasero_layout_new ();
	gtk_widget_show (obj->priv->layout);
	gtk_notebook_append_page (GTK_NOTEBOOK (obj), obj->priv->layout, NULL);

	g_signal_connect (obj->priv->layout,
			  "sidepane",
			  G_CALLBACK (brasero_project_manager_sidepane_changed),
			  obj);


	obj->priv->project = brasero_project_new ();

#ifdef BUILD_PREVIEW

	GtkWidget *preview;

	preview = brasero_preview_new ();
	gtk_widget_show (preview);
	brasero_preview_add_source (BRASERO_PREVIEW (preview),
				    BRASERO_URI_CONTAINER (obj->priv->project));

#endif

	chooser = brasero_file_chooser_new ();
    	BRASERO_PROJECT_MANAGER_CONNECT_CHANGED (obj, chooser);

	gtk_widget_show_all (chooser);
	brasero_layout_add_source (BRASERO_LAYOUT (obj->priv->layout),
				   chooser,
				   "Chooser",
				   _("Browse the file system"),
				   GTK_STOCK_DIRECTORY,
				   BRASERO_LAYOUT_AUDIO|BRASERO_LAYOUT_DATA|BRASERO_LAYOUT_VIDEO);

#ifdef BUILD_PREVIEW
	brasero_preview_add_source (BRASERO_PREVIEW (preview),
				    BRASERO_URI_CONTAINER (chooser));
#endif

	brasero_layout_add_project (BRASERO_LAYOUT (obj->priv->layout),
				    obj->priv->project);
	gtk_widget_show (obj->priv->project);

#ifdef BUILD_PLAYLIST
	GtkWidget *playlist;

	playlist = brasero_playlist_new ();
    	BRASERO_PROJECT_MANAGER_CONNECT_CHANGED (obj, playlist);
	gtk_widget_show_all (playlist);
	brasero_layout_add_source (BRASERO_LAYOUT (obj->priv->layout),
				   playlist,
				   "Playlist",
				   _("Display playlists and their contents"),
				   "audio-x-generic",
				   BRASERO_LAYOUT_AUDIO);

#ifdef BUILD_PREVIEW
	brasero_preview_add_source (BRASERO_PREVIEW (preview),
				    BRASERO_URI_CONTAINER (playlist));
#endif

#endif

#ifdef BUILD_PREVIEW
	brasero_layout_add_preview (BRASERO_LAYOUT (obj->priv->layout),
				    preview);
#endif

}
