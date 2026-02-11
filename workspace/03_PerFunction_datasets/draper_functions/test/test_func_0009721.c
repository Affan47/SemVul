add_clicked (GtkWidget * button, GladeEPropIconSources * eprop_sources)
{

  GtkTreeIter *parent_iter = NULL, iter, new_parent_iter;
  GtkTreePath *new_item_path;
  gchar *icon_name;
  gchar *selected_icon_name = NULL;
  gint index;
  RowEditData *edit_data;

  selected_icon_name = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT (eprop_sources->combo));

  if (!selected_icon_name)
    return;


  if (gtk_tree_model_get_iter_first (GTK_TREE_MODEL (eprop_sources->store), &iter))
    {
      do
        {
          gtk_tree_model_get (GTK_TREE_MODEL (eprop_sources->store), &iter,
                              COLUMN_TEXT, &icon_name, -1);

          if (icon_name && strcmp (icon_name, selected_icon_name) == 0)
            parent_iter = gtk_tree_iter_copy (&iter);

          g_free (icon_name);
        }
      while (parent_iter == NULL &&
             gtk_tree_model_iter_next (GTK_TREE_MODEL (eprop_sources->store), &iter));
    }


  if (parent_iter &&
      gtk_tree_model_iter_children (GTK_TREE_MODEL (eprop_sources->store),
                                    &iter, parent_iter))
    {
      do
        {
          gtk_tree_model_get (GTK_TREE_MODEL (eprop_sources->store), &iter,
                              COLUMN_LIST_INDEX, &index, -1);


          if (index < 0)
            goto expand_to_path_and_focus;

        }
      while (gtk_tree_model_iter_next (GTK_TREE_MODEL (eprop_sources->store), &iter));
    }

  if (!parent_iter)
    {

      gtk_tree_store_append (eprop_sources->store, &new_parent_iter, NULL);
      gtk_tree_store_set (eprop_sources->store, &new_parent_iter,
                          COLUMN_TEXT, selected_icon_name,
                          COLUMN_TEXT_EDITABLE, FALSE,
                          COLUMN_TEXT_WEIGHT, PANGO_WEIGHT_BOLD, -1);
      parent_iter = gtk_tree_iter_copy (&new_parent_iter);
    }

  gtk_tree_store_append (eprop_sources->store, &iter, parent_iter);
  gtk_tree_store_set (eprop_sources->store, &iter,
                      COLUMN_ICON_NAME, selected_icon_name,
                      COLUMN_TEXT_EDITABLE, TRUE,
                      COLUMN_TEXT_WEIGHT, PANGO_WEIGHT_NORMAL,
                      COLUMN_LIST_INDEX, -1, -1);


expand_to_path_and_focus:
  new_item_path = gtk_tree_model_get_path (GTK_TREE_MODEL (eprop_sources->store), &iter);


  edit_data = g_slice_new (RowEditData);
  edit_data->eprop = eprop_sources;
  edit_data->row_ref = gtk_tree_row_reference_new (GTK_TREE_MODEL (eprop_sources->store), new_item_path);
  g_idle_add ((GSourceFunc)edit_row_idle, edit_data);

  g_free (selected_icon_name);
  gtk_tree_path_free (new_item_path);
  gtk_tree_iter_free (parent_iter);
}
