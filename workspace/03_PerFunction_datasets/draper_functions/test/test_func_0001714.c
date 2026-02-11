add_button_clicked (GtkWidget  *button,
                    GtkBuilder *builder)
{
  GtkTreeView *treeview;
  GtkTreeModel *model;
  GtkTreeModel *section_model;
  GtkTreeIter iter;
  gboolean found, cont;

  treeview = GTK_TREE_VIEW (gtk_builder_get_object (builder,
                                                    "shortcut_treeview"));
  model = gtk_tree_view_get_model (treeview);


  section_model = gtk_tree_view_get_model (GTK_TREE_VIEW (WID (builder, "section_treeview")));
  cont = gtk_tree_model_get_iter_first (section_model, &iter);
  found = FALSE;
  while (cont)
    {
      BindingGroupType group;

      gtk_tree_model_get (section_model, &iter,
                          SECTION_GROUP_COLUMN, &group,
                          -1);

      if (group == BINDING_GROUP_USER)
        {
          found = TRUE;
          break;
        }
      cont = gtk_tree_model_iter_next (section_model, &iter);
    }
  if (found)
    {
      GtkTreeSelection *selection;

      selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (WID (builder, "section_treeview")));
      gtk_tree_selection_select_iter (selection, &iter);
    }


  add_custom_shortcut (treeview, model);
}
