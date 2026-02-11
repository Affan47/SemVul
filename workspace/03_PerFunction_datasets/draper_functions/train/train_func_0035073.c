populate_log_tab(struct w *widgets)
{

    FILE *fp;
    long file_size;
    char *line;
    GtkTreeIter iter;
    GtkTreePath *path;
    gboolean edit=0;
    int found = 0;
    gchar *utf8=NULL, *log_path;

    gtk_list_store_clear(widgets->log_store);

    log_path = g_strdup_printf("/var/log/gadmin-openvpn/client/%s/openvpn-client.log", selected_connection);

    if((fp=fopen(log_path, "r"))==NULL)
    {

	g_free(log_path);
        return;
    }
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    rewind(fp);

    line = allocate(file_size+1);

    if( file_size > 1 )
    while(fgets(line, file_size, fp)!=NULL)
    {
	if( line[strlen(line)-1]=='\n' )
	  line[strlen(line)-1]='\0';

	found = 1;

	gtk_list_store_append(GTK_LIST_STORE(widgets->log_store), &iter);
	utf8 = g_locale_to_utf8(line, strlen(line), NULL, NULL, NULL);
	gtk_list_store_set(GTK_LIST_STORE(widgets->log_store), &iter, 0, utf8, -1);
	if(utf8!=NULL)
          g_free(utf8);
    }
    fclose(fp);
    free(line);
    g_free(log_path);

    if( ! found )
      return;

    path = gtk_tree_path_new_first();
    gtk_tree_view_set_cursor(GTK_TREE_VIEW(widgets->log_treeview), path, NULL, edit);
    gtk_tree_path_free(path);
}
