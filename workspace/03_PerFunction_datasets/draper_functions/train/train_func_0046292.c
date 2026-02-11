glade_gtk_store_read_columns (GladeWidget *widget, GladeXmlNode *node)
{
	GladeNameContext *context;
	GladeXmlNode *columns_node;
	GladeProperty *property;
	GladeXmlNode *prop;
	GList *types = NULL;
	GValue value = {0,};
	gchar column_name[256];

	column_name[0] = '\0';
	column_name[255] = '\0';

	if ((columns_node = glade_xml_search_child (node, GLADE_TAG_COLUMNS)) == NULL)
		return;

	context = glade_name_context_new ();

	for (prop = glade_xml_node_get_children_with_comments (columns_node); prop;
	     prop = glade_xml_node_next_with_comments (prop))
	{
		GladeColumnType *data;
		gchar *type, *comment_str, buffer[256];

		if (!glade_xml_node_verify_silent (prop, GLADE_TAG_COLUMN) &&
		    !glade_xml_node_is_comment (prop)) continue;

		if (glade_xml_node_is_comment (prop))
		{
			comment_str = glade_xml_get_content (prop);
			if (sscanf (comment_str, " column-name %s", buffer) == 1)
				strncpy (column_name, buffer, 255);

			g_free (comment_str);
			continue;
		}

		type = glade_xml_get_property_string_required (prop, GLADE_TAG_TYPE, NULL);

		data              = glade_column_type_new (type, NULL);
		data->type_name   = g_strdup (type);
		data->column_name = column_name[0] ? g_strdup (column_name) : g_ascii_strdown (type, -1);

		if (glade_name_context_has_name (context, data->column_name))
		{
			gchar *name = glade_name_context_new_name (context, data->column_name);
			g_free (data->column_name);
			data->column_name = name;
		}
		glade_name_context_add_name (context, data->column_name);

		types = g_list_prepend (types, data);
		g_free (type);

		column_name[0] = '\0';
	}

	property = glade_widget_get_property (widget, "columns");
	g_value_init (&value, GLADE_TYPE_COLUMN_TYPE_LIST);
	g_value_take_boxed (&value, g_list_reverse (types));
	glade_property_set_value (property, &value);
	g_value_unset (&value);
}
