print_files (FilebrowserBackend *directory, gpointer user_data){
  if (!directory || !user_data) return ;
  gphpeditFileBrowserPrivate *priv = (gphpeditFileBrowserPrivate *) user_data;
  gphpedit_debug(DEBUG_FILEBROWSER);

  GSList *l;
  GtkTreeIter iter2;
  GtkTreeIter* iter=NULL;
  gtk_tree_store_clear(priv->pTree);
  for (l = get_filebrowser_backend_files(directory); l != NULL; l = g_slist_next (l)) {
    FOLDERFILE *current=(FOLDERFILE *) l->data;
    gphpedit_debug_message(DEBUG_FILEBROWSER,"File added -> name: '%s' \tmime: '%s'", current->display_name, current->mime);
    GIcon *icon= g_icon_new_for_string (current->icon,NULL);
    gtk_tree_store_insert_with_values(GTK_TREE_STORE(priv->pTree), &iter2, iter, 0, ICON_COLUMN, icon, FILE_COLUMN, current->display_name,MIME_COLUMN,current->mime,-1);
    g_object_unref(icon);
  }
  if (get_filebrowser_backend_number_files(priv->fbbackend)!=0){
    priv->cache_model=gtk_tree_view_get_model (GTK_TREE_VIEW(priv->pListView));
    search_control_sensible(priv,TRUE);
  } else {
    search_control_sensible(priv,FALSE);
  }
}
