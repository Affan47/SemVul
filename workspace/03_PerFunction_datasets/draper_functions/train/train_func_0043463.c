send_fax_impl(void) {

  std::pair<std::string, std::string> fax_to_send;

  GtkTreeIter selected_iter;
  GtkTreeModel* model_p;
  GtkTreeSelection* selection_p = gtk_tree_view_get_selection(tree_view_p);

  if (gtk_tree_selection_get_selected(selection_p, &model_p, &selected_iter)) {
    gchar* fax_label_p = 0;
    gchar* fax_filename_p = 0;
    gtk_tree_model_get(model_p, &selected_iter,
		       ModelColumns::fax_label, &fax_label_p,
		       ModelColumns::fax_filename, &fax_filename_p,
		       -1);
    if (fax_label_p) fax_to_send.first = fax_label_p;
    if (fax_filename_p) fax_to_send.second = fax_filename_p;


    g_free(fax_label_p);
    g_free(fax_filename_p);

    selected_fax(fax_to_send);
  }
}
