change_callback(GtkWidget *w, gpointer data)
{
  struct worklist_data *ptr;
  GtkTreeSelection *selection;
  GtkTreeModel *model;
  GtkTreeIter it;

  ptr = data;
  selection = ptr->src_selection;

  if (gtk_tree_selection_get_selected(selection, &model, &it)) {
    gint cid;

    gtk_tree_model_get(model, &it, 0, &cid, -1);

    city_change_production(ptr->pcity, cid_production(cid));
  }
}
