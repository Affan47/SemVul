glade_gtk_cell_layout_read_child (GladeWidgetAdaptor *adaptor,
				  GladeWidget        *widget,
				  GladeXmlNode       *node)
{
	GladeXmlNode *widget_node;
	GladeWidget  *child_widget;
	gchar        *internal_name;

	if (!glade_xml_node_verify (node, GLADE_XML_TAG_CHILD))
		return;

	internal_name = glade_xml_get_property_string (node, GLADE_XML_TAG_INTERNAL_CHILD);

	if ((widget_node =
	     glade_xml_search_child
	     (node, GLADE_XML_TAG_WIDGET(glade_project_get_format(widget->project)))) != NULL)
	{

		if ((child_widget = glade_widget_read (widget->project,
						       widget, widget_node,
						       internal_name)) != NULL)
		{


			if (!internal_name)
			{
				glade_widget_add_child (widget, child_widget, FALSE);

				glade_gtk_cell_renderer_read_attributes (child_widget, node);

				g_idle_add ((GSourceFunc)glade_gtk_cell_renderer_sync_attributes,
					    child_widget->object);
			}
		}
	}
	g_free (internal_name);
}
