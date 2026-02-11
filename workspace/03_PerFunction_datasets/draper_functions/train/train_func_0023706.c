populate_security(struct w *widgets)
{

    FILE *fp;
    long file_size;
    char *buffy;
    GtkTreeIter iter;
    GtkTreePath *path;
    gboolean edit=0;
    int found = 0;
    gchar *utf8=NULL;


    gtk_list_store_clear(widgets->security_store);


    if((fp=fopen("/var/log/samba/samba.log", "r"))==NULL)
    {


        return;
    }
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    rewind(fp);

    buffy = allocate(file_size+1024);

    if( file_size > 1 )
    while(fgets(buffy, file_size, fp)!=NULL)
    {
	if( strlen(buffy) < 10 )
	  continue;

	found = 1;
    	gtk_list_store_append(GTK_LIST_STORE(widgets->security_store), &iter);
    	utf8 = g_locale_to_utf8(buffy, strlen(buffy)-1, NULL, NULL, NULL);
    	gtk_list_store_set(GTK_LIST_STORE(widgets->security_store), &iter, 0, utf8, -1);
    }
    fclose(fp);
    free(buffy);

    if(utf8!=NULL)
      g_free(utf8);


    if( ! found )
      return;

    path = gtk_tree_path_new_first();
    gtk_tree_view_set_cursor(GTK_TREE_VIEW(widgets->security_treeview), path, NULL, edit);
    gtk_tree_path_free(path);
}
