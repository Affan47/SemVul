on_okbutton2_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *dialog3;
	GtkEntry *entry;
	gint mkres;
	GError **error = NULL;
	gboolean success = FALSE;
	int result;


	entry = (GtkEntry *)lookup_widget(GTK_WIDGET(button), "entry12");
	global_track_dir = g_strconcat(gtk_entry_get_text(entry),"/",NULL);

	result = strncmp(global_track_dir, "~", 1);

	if(!result)
	{
		char *sub_home, *home_dir;

		strsep(&global_track_dir, "~");
		sub_home = g_strdup(strsep(&global_track_dir, "~"));
		home_dir = getenv("HOME");

		g_free(global_track_dir);
		global_track_dir = g_strconcat(home_dir, sub_home, NULL);

		g_free(sub_home);
	}


	printf("TRACKDIR: %s - ~ %d\n",global_track_dir, result);


	mkres = g_mkdir_with_parents(global_track_dir,0700);
	if(mkres==-1) {
		printf("MKDIR ERROR\n\n");
		perror("mkdir........");
	}

	success = gconf_client_set_string(
				global_gconfclient,
				GCONF"/track_dir",
				global_track_dir,
				error);

	dialog3 = lookup_widget(GTK_WIDGET(button), "dialog3");

	gtk_widget_hide(dialog3);
}
