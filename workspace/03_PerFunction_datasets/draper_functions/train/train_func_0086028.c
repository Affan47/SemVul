_add_tree_node (gftp_bookmarks_var * entry, char *path, int isleaf,
                int expanded)
{
  static GdkPixmap * closedir_pixmap = NULL,
                   * opendir_pixmap = NULL;
  static GdkBitmap * closedir_bitmap = NULL,
                   * opendir_bitmap = NULL;
  static int initialized = 0;
  GtkCTreeNode * parent;
  char *text[2], *pos;

  if (!initialized)
    {
      gftp_get_pixmap (tree, "open_dir.xpm", &opendir_pixmap, &opendir_bitmap);
      gftp_get_pixmap (tree, "dir.xpm", &closedir_pixmap, &closedir_bitmap);
      initialized = 1;
    }

  if (path == NULL)
    {
      if ((pos = strrchr (entry->path, '/')) == NULL)
        pos = entry->path;
      else
        pos++;
    }
  else
    pos = path;

  text[0] = text[1] = pos;

  if (entry->prev == NULL)
    parent = NULL;
  else
    parent = entry->prev->cnode;

  if (isleaf)
    entry->cnode = gtk_ctree_insert_node (GTK_CTREE (tree), parent, NULL, text,
                                          5, NULL, NULL, NULL, NULL, TRUE,
                                          expanded);
  else
    entry->cnode = gtk_ctree_insert_node (GTK_CTREE (tree), parent, NULL,
                                          text, 5, closedir_pixmap,
                                          closedir_bitmap, opendir_pixmap,
                                          opendir_bitmap, FALSE, expanded);

  gtk_ctree_node_set_row_data (GTK_CTREE (tree), entry->cnode, entry);
}
