glade_gtk_store_write_data (GladeWidget * widget,
                            GladeXmlContext * context, GladeXmlNode * node)
{
  GladeXmlNode *data_node, *col_node, *row_node;
  GList *columns = NULL;
  GladeModelData *data;
  GNode *data_tree = NULL, *row, *iter;
  gint colnum;

  glade_widget_property_get (widget, "data", &data_tree);
  glade_widget_property_get (widget, "columns", &columns);


  if (!data_tree || !columns)
    return;

  data_node = glade_xml_node_new (context, GLADE_TAG_DATA);

  for (row = data_tree->children; row; row = row->next)
    {
      row_node = glade_xml_node_new (context, GLADE_TAG_ROW);
      glade_xml_node_append_child (data_node, row_node);

      for (colnum = 0, iter = row->children; iter; colnum++, iter = iter->next)
        {
          gchar *string, *column_number;

          data = iter->data;


          if (G_VALUE_TYPE (&data->value) == 0 ||
              G_VALUE_TYPE (&data->value) == G_TYPE_POINTER)
            continue;

          string = glade_utils_string_from_value (&data->value);


          if (!g_list_nth (columns, colnum))
            break;

          column_number = g_strdup_printf ("%d", colnum);

          col_node = glade_xml_node_new (context, GLADE_TAG_COL);
          glade_xml_node_append_child (row_node, col_node);
          glade_xml_node_set_property_string (col_node, GLADE_TAG_ID,
                                              column_number);
          glade_xml_set_content (col_node, string);

          if (data->i18n_translatable)
            glade_xml_node_set_property_string (col_node,
                                                GLADE_TAG_TRANSLATABLE,
                                                GLADE_XML_TAG_I18N_TRUE);
          if (data->i18n_context)
            glade_xml_node_set_property_string (col_node,
                                                GLADE_TAG_CONTEXT,
                                                data->i18n_context);
          if (data->i18n_comment)
            glade_xml_node_set_property_string (col_node,
                                                GLADE_TAG_COMMENT,
                                                data->i18n_comment);


          g_free (column_number);
          g_free (string);
        }
    }

  if (!glade_xml_node_get_children (data_node))
    glade_xml_node_delete (data_node);
  else
    glade_xml_node_append_child (node, data_node);
}
