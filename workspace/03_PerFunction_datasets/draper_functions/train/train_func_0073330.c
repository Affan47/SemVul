ui_time_dialog_set_times(GtkWidget * dialog) {

  ui_time_dialog_t * td;
  GtkTreeSelection *selection;
  GtkTreeModel * model;
  GList * selected_sets;
  GList * temp_sets;


  g_return_if_fail(dialog != NULL);

  td = g_object_get_data(G_OBJECT(dialog), "td");

  while(td->data_sets != NULL)
    remove_data_set(dialog, td->data_sets->data);

  selected_sets = amitk_object_get_selected_children_of_type(AMITK_OBJECT(td->study),
							     AMITK_OBJECT_TYPE_DATA_SET,
							     AMITK_SELECTION_ANY, TRUE);
  temp_sets = selected_sets;
  while (temp_sets != NULL) {
    add_data_set(dialog, temp_sets->data);
    temp_sets = temp_sets->next;
  }
  amitk_objects_unref(selected_sets);

  model = gtk_tree_view_get_model(GTK_TREE_VIEW(td->tree_view));
  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(td->tree_view));

  update_model(GTK_LIST_STORE(model), selection,td->data_sets);

  update_selections(model, selection, dialog, td);
  update_entries(dialog, td);

  return;
}
