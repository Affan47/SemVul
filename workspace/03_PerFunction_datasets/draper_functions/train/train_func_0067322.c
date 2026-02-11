glade_eprop_model_data_add_row (GladeEditorProperty * eprop)
{
  GladeEPropModelData *eprop_data = GLADE_EPROP_MODEL_DATA (eprop);
  GValue value = { 0, };
  GNode *node = NULL;
  GList *columns = NULL;
  GladeProperty *property = glade_editor_property_get_property (eprop);

  glade_property_get (property, &node);
  glade_widget_property_get (glade_property_get_widget (property), "columns", &columns);

  if (!columns)
    return;

  clear_view (eprop);

  if (!node)
    node = g_node_new (NULL);
  else
    node = glade_model_data_tree_copy (node);

  append_row (node, columns);

  eprop_data->adding_row = TRUE;

  g_value_init (&value, GLADE_TYPE_MODEL_DATA_TREE);
  g_value_take_boxed (&value, node);
  glade_editor_property_commit (eprop, &value);
  g_value_unset (&value);

  eprop_data->adding_row = FALSE;
}
