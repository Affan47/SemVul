_filebrowser_sort_func(GtkTreeModel * model, GtkTreeIter * a, GtkTreeIter * b,
               gpointer user_data)
{
  gchar *namea, *nameb, *mimea, *mimeb;
  gboolean isdira, isdirb;
  gint retval = 0;
  gtk_tree_model_get(GTK_TREE_MODEL (model), a, FILE_COLUMN, &namea,MIME_COLUMN, &mimea,-1);
  gtk_tree_model_get(GTK_TREE_MODEL (model), b, FILE_COLUMN, &nameb,MIME_COLUMN, &mimeb,-1);
  isdira = (mimea && MIME_ISDIR(mimea));
  isdirb = (mimeb && MIME_ISDIR(mimeb));
  gphpedit_debug_message(DEBUG_FILEBROWSER, "isdira=%d, mimea=%s, isdirb=%d, mimeb=%s",isdira,mimea,isdirb,mimeb);
  if (isdira == isdirb) {
    if (namea == nameb) {
      retval = 0;
    } else if (namea == NULL || nameb == NULL) {
      retval = (namea - nameb);
    } else {
      gchar *dota, *dotb;
      dota = strrchr(namea, '.');
      dotb = strrchr(nameb, '.');
      if (dota)
        *dota = '\0';
      if (dotb)
        *dotb = '\0';
      retval = strcmp(namea, nameb);
      if (retval == 0) {
        if (dota)
          *dota = '.';
        if (dotb)
          *dotb = '.';
        retval = strcmp(namea, nameb);
      }
    }
  } else {
    retval = (isdirb - isdira);
  }
  g_free(namea);
  g_free(nameb);
  g_free(mimea);
  g_free(mimeb);
  return retval;
}
