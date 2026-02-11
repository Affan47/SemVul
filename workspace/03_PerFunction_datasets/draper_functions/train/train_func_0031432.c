update_dialog_treeview (DialogData *data)
{
  GVariantIter iter;
  gint disk_slot;
  const gchar *disk_block_objpath;
  const gchar **disk_states;
  guint64 disk_num_errors;
  GtkTreeIter titer;
  UDisksBlock *selected_block = NULL;
  GtkTreeIter *iter_to_select = NULL;


  if (gtk_tree_selection_get_selected (gtk_tree_view_get_selection (GTK_TREE_VIEW (data->treeview)),
                                       NULL,
                                       &titer))
    {
      gtk_tree_model_get (GTK_TREE_MODEL (data->store),
                          &titer,
                          COLUMN_BLOCK, &selected_block,
                          -1);
    }
  gtk_list_store_clear (data->store);
  g_variant_iter_init (&iter, udisks_mdraid_get_active_devices (data->mdraid));
  while (g_variant_iter_next (&iter, "(&oi^a&sta{sv})",
                              &disk_block_objpath,
                              &disk_slot,
                              &disk_states,
                              &disk_num_errors,
                              NULL))
    {
      UDisksObject *object = NULL;
      UDisksBlock *block = NULL;
      GtkTreeIter inserted_iter;

      object = udisks_client_peek_object (data->client, disk_block_objpath);
      if (object != NULL)
        {
          block = udisks_object_peek_block (object);
        }

      gtk_list_store_insert_with_values (data->store,
                                         &inserted_iter,
                                         -1,
                                         COLUMN_SLOT, disk_slot,
                                         COLUMN_BLOCK, block,
                                         COLUMN_STATES, disk_states,
                                         COLUMN_NUM_ERRORS, (guint64) disk_num_errors,
                                         -1);
      if (block == selected_block)
        iter_to_select = gtk_tree_iter_copy (&inserted_iter);

      g_free (disk_states);
    }
  if (iter_to_select == NULL)
    {
      GtkTreeIter first_iter;
      if (gtk_tree_model_get_iter_first (GTK_TREE_MODEL (data->store), &first_iter))
        iter_to_select = gtk_tree_iter_copy (&first_iter);
    }
  if (iter_to_select != NULL)
    {
      gtk_tree_selection_select_iter (gtk_tree_view_get_selection (GTK_TREE_VIEW (data->treeview)),
                                      iter_to_select);
      gtk_tree_iter_free (iter_to_select);
    }
  g_clear_object (&selected_block);
}
