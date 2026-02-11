glade_gtk_image_menu_item_read_widget (GladeWidgetAdaptor *adaptor,
				       GladeWidget        *widget,
				       GladeXmlNode       *node)
{
	GladeProperty *property;
	gboolean use_stock;
	gchar *label = NULL;

	if (!glade_xml_node_verify
	    (node, GLADE_XML_TAG_WIDGET (glade_project_get_format (widget->project))))
		return;


        GWA_GET_CLASS (GTK_TYPE_MENU_ITEM)->read_widget (adaptor, widget, node);


	glade_gtk_image_menu_item_fix_stock_item (widget);

	glade_widget_property_get (widget, "use-stock", &use_stock);
	if (use_stock)
	{
		property = glade_widget_get_property (widget, "label");

		glade_property_get (property, &label);
		glade_widget_property_set (widget, "use-underline", TRUE);
		glade_widget_property_set (widget, "stock", label);
		glade_property_sync (property);
	}


	property = glade_widget_get_property (widget, "use-stock");
	glade_property_sync (property);


	if (glade_project_get_format (widget->project) == GLADE_PROJECT_FORMAT_GTKBUILDER)
		g_signal_connect (G_OBJECT (widget->project), "parse-finished",
				  G_CALLBACK (glade_gtk_image_menu_item_parse_finished),
				  widget);
}
