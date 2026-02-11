data_set_selection_changed_cb(GtkTreeSelection * selection, gpointer data) {

  tb_alignment_t * tb_alignment = data;
  AmitkDataSet * ds;
  gboolean fixed_ds;
  gboolean can_continue;
  GtkTreeIter iter;
  GtkTreeModel * model;

  fixed_ds = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(selection), "fixed"));

  if (gtk_tree_selection_get_selected (selection, &model, &iter)) {

    gtk_tree_model_get(model, &iter, COLUMN_DATA_SET_POINTER, &ds, -1);
    g_return_if_fail(AMITK_IS_DATA_SET(ds));

    if (fixed_ds) {
      if (tb_alignment->fixed_ds != NULL) amitk_object_unref(tb_alignment->fixed_ds);
      tb_alignment->fixed_ds = amitk_object_ref(ds);
    } else {
      if (tb_alignment->moving_ds != NULL) amitk_object_unref(tb_alignment->moving_ds);
      tb_alignment->moving_ds = amitk_object_ref(ds);
    }
  } else {
    if (fixed_ds) {
      if (tb_alignment->fixed_ds != NULL) amitk_object_unref(tb_alignment->fixed_ds);
      tb_alignment->fixed_ds = NULL;
    } else {
      if (tb_alignment->moving_ds != NULL) amitk_object_unref(tb_alignment->moving_ds);
      tb_alignment->moving_ds = NULL;
    }
  }

  can_continue = ((tb_alignment->fixed_ds != NULL) &&
		  (tb_alignment->moving_ds != NULL) &&
		  (tb_alignment->fixed_ds != tb_alignment->moving_ds));

  gtk_assistant_set_page_complete(GTK_ASSISTANT(tb_alignment->dialog),
				  tb_alignment->page[DATA_SETS_PAGE],
				  can_continue);
  return;
}
