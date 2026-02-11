fs_create(GtkWidget *vbox, gint first_create)
	{
	GList	*list;
	FSmon	*fs;
	gint	i;

	if (fs_main_vbox == NULL)
		{
		fs_main_vbox = gtk_vbox_new(FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vbox), fs_main_vbox, FALSE, FALSE, 0);
		gtk_widget_show(fs_main_vbox);

		fs_secondary_vbox = gtk_vbox_new(FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vbox), fs_secondary_vbox, FALSE, FALSE, 0);
		gtk_widget_show(fs_secondary_vbox);
		secondary_monitors_shown = FALSE;
		}
	n_fs_monitors = 0;
	for (i = 0, list = fs_mon_list; list; ++i, list = list->next)
		{
		fs = (FSmon *)list->data;
		fs_monitor_create(fs->secondary ? fs_secondary_vbox : fs_main_vbox,fs,
					i, first_create);
		}
	if (g_list_length(fs_mon_list) == 0)
		gkrellm_spacers_hide(mon_fs);
	}
