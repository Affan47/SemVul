selection_changed_cb (GtkTreeSelection *tree_sel, ggobid *gg)
{
  gint j;
  GGobiData *d = datad_get_from_notebook (gg->vartable_ui.notebook, gg);
  vartabled *vt;
  GList *rows, *l;
  GtkTreeModel *model;

  for (j = 0 ; j < d->ncols ; j++) {
    vt = vartable_element_get (j, d);
	vt->selected = false;
  }

  rows = gtk_tree_selection_get_selected_rows(tree_sel, &model);
  for (l = rows; l; l = l->next) {
    gint varno;
    GtkTreePath *path = (GtkTreePath*)l->data;
    varno = vartable_varno_from_path(model, path);
    gtk_tree_path_free(path);

    vt = vartable_element_get (varno, d);
    vt->selected = true;
  }
  g_list_free(rows);
}
