save_dialog_list_callback(GtkTreeSelection *selection,
                                      gpointer data)
{
  struct save_dialog *pdialog = data;
  GtkTreeModel *model;
  GtkTreeIter iter;
  const gchar *filename;

  if (!gtk_tree_selection_get_selected(selection, &model, &iter)) {
    gtk_dialog_set_response_sensitive(pdialog->shell, SD_RES_DELETE, FALSE);
    return;
  }

  gtk_dialog_set_response_sensitive(pdialog->shell, SD_RES_DELETE, TRUE);
  gtk_tree_model_get(model, &iter, SD_COL_PRETTY_NAME, &filename, -1);
  gtk_entry_set_text(pdialog->entry, filename);
}
