_drawPix(GtkCellLayout *layout _U_, GtkCellRenderer *cell,
                     GtkTreeModel *model, GtkTreeIter *iter, gpointer data)
{
  GdkPixbuf *pix;

  if (GPOINTER_TO_INT(data))
    gtk_tree_model_get(model, iter, COLUMN_COLOR_PIXBUF_ALPHA, &pix, -1);
  else
    gtk_tree_model_get(model, iter, COLUMN_COLOR_PIXBUF, &pix, -1);

  if (pix)
    {
      g_object_set(G_OBJECT(cell), "pixbuf", pix, NULL);
      g_object_unref(pix);
    }
  else
    g_object_set(G_OBJECT(cell), "icon-name", "list-add", NULL);
}
