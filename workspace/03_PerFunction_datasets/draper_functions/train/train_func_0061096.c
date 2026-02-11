eprop_column_append (GladeEditorProperty *eprop,
                     const gchar         *type_name,
		     const gchar         *column_name)
{
  GladeEPropColumnTypes *eprop_types = GLADE_EPROP_COLUMN_TYPES (eprop);
  GList *columns = NULL;
  GladeColumnType *data;
  GValue value = { 0, };
  GladeProperty *property;

  property = glade_editor_property_get_property (eprop);

  glade_property_get (property, &columns);
  if (columns)
    columns = glade_column_list_copy (columns);

  data = glade_column_type_new (type_name, column_name);

  columns = g_list_append (columns, data);

  eprop_types->adding_column = TRUE;
  glade_command_push_group (_("Setting columns on %s"),
                            glade_widget_get_name (glade_property_get_widget (property)));

  g_value_init (&value, GLADE_TYPE_COLUMN_TYPE_LIST);
  g_value_take_boxed (&value, columns);
  glade_editor_property_commit (eprop, &value);

  eprop_column_adjust_rows (eprop, columns);
  g_value_unset (&value);

  glade_command_pop_group ();

  eprop_types->adding_column = FALSE;
}
