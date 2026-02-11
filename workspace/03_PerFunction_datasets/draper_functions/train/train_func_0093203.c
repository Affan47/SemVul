tree_model_refresh(struct model_pak *model)
{
gboolean flag=FALSE;
GSList *list;
GtkTreeIter root, branch, active;
GdkPixbuf *pixbuf;
GtkTreeSelection *selection;


if (!model)
  return;
if (!tree_model_iter(&root, model))
  return;

selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(sysenv.tree));


gtk_tree_store_set(sysenv.tree_store, &root, TREE_NAME, model->basename, -1);


pixbuf = gdk_pixbuf_new_from_xpm_data((const gchar **) graph_xpm);
for (list=model->graph_list ; list ; list=g_slist_next(list))
  {
  if (graph_grafted(list->data))
    continue;

  gtk_tree_store_append(sysenv.tree_store, &branch, &root);
  gtk_tree_store_set(sysenv.tree_store, &branch,
                     TREE_PIXMAP, pixbuf,
                     TREE_NAME, graph_treename(list->data),
                     TREE_POINTER, model,
                     TREE_DATA, list->data,
                     -1);
  graph_set_grafted(TRUE, list->data);

  if (selection)
    {
    active = branch;
    flag = TRUE;
    }
  }


gtk_tree_view_expand_all(GTK_TREE_VIEW(sysenv.tree));
if (flag)
  gtk_tree_selection_select_iter(selection, &active);
}
