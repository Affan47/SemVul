populate_backup_combo(struct w *widgets)
{
    int i = 0, x = 0, count = 0;
    struct dirent **namelist;
    gchar *conf_file, *utf8=NULL;
    GtkTreeModel *model;


    g_signal_handler_block(GTK_WIDGET(widgets->rsync_set_combo[0]), backup_combo_changed_signal);


    global_backup_name = gtk_combo_box_get_active_text(GTK_COMBO_BOX(widgets->rsync_set_combo[0]));


    model = gtk_combo_box_get_model(GTK_COMBO_BOX(widgets->rsync_set_combo[0]));


    gtk_list_store_clear(GTK_LIST_STORE(model));


    i = scandir(global_settings_dir, &namelist, 0, alphasort);
    if( i < 0 )
    {
	perror("scandir");
	return 0;
    }

    for(x=0; x<i; x++)
    {

	if( strcmp(namelist[x]->d_name, ".")  == 0
	||  strcmp(namelist[x]->d_name, "..") == 0 )
	{
	    free(namelist[x]);
	    continue;
	}


	utf8 = g_locale_to_utf8(namelist[x]->d_name, strlen(namelist[x]->d_name), NULL, NULL, NULL);

	gtk_combo_box_append_text(GTK_COMBO_BOX(widgets->rsync_set_combo[0]), utf8);


	if( count == 0 && global_backup_name == NULL )
	{
	    count++;

	    gtk_combo_box_set_active(GTK_COMBO_BOX(widgets->rsync_set_combo[0]), 0);


	    conf_file = g_strdup_printf("%s/%s", global_settings_dir, namelist[x]->d_name);
	    global_backup_name = g_strdup_printf("%s", namelist[x]->d_name);
	}


	if( global_backup_name!=NULL && strcmp(global_backup_name, namelist[x]->d_name) == 0 )
	{
	    gtk_combo_box_set_active(GTK_COMBO_BOX(widgets->rsync_set_combo[0]), x-2);


	    conf_file = g_strdup_printf("%s/%s", global_settings_dir, namelist[x]->d_name);
	    global_backup_name = g_strdup_printf("%s", namelist[x]->d_name);
	}
	g_free(utf8);
	free(namelist[x]);

	count++;
    }
    free(namelist);


    g_signal_handler_unblock(GTK_WIDGET(widgets->rsync_set_combo[0]), backup_combo_changed_signal);

    return count;
}
