data_changed_idle (GladeEditorProperty * eprop)
{
  GladeEPropModelData *eprop_data = GLADE_EPROP_MODEL_DATA (eprop);
  GladeProperty *property = glade_editor_property_get_property (eprop);
  GNode *data_tree = NULL, *new_tree, *row;
  GtkTreeIter iter;
  gint rownum;

  glade_property_get (property, &data_tree);
  g_assert (data_tree);

  new_tree = g_node_new (NULL);

  if (gtk_tree_model_get_iter_first (GTK_TREE_MODEL (eprop_data->store), &iter))
    {
      do
        {
          gtk_tree_model_get (GTK_TREE_MODEL (eprop_data->store), &iter,
                              COLUMN_ROW, &rownum, -1);


          if ((row = g_node_nth_child (data_tree, rownum)) != NULL)
            {

              row = glade_model_data_tree_copy (row);
              g_node_append (new_tree, row);
            }
        }
      while (gtk_tree_model_iter_next
             (GTK_TREE_MODEL (eprop_data->store), &iter));
    }


  if (eprop_data->pending_data_tree)
    glade_model_data_tree_free (eprop_data->pending_data_tree);
  eprop_data->pending_data_tree = new_tree;
  update_data_tree_idle (eprop);

  return FALSE;
}
