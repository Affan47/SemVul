glade_gtk_window_read_widget (GladeWidgetAdaptor * adaptor,
                              GladeWidget * widget, GladeXmlNode * node)
{
  if (!(glade_xml_node_verify_silent (node, GLADE_XML_TAG_WIDGET) ||
	glade_xml_node_verify_silent (node, GLADE_XML_TAG_TEMPLATE)))
    return;


  GWA_GET_CLASS (GTK_TYPE_WIDGET)->read_widget (adaptor, widget, node);


  if (glade_widget_property_original_default (widget, "icon") == FALSE)
    glade_widget_property_set (widget, "glade-window-icon-name", FALSE);
  else
    glade_widget_property_set (widget, "glade-window-icon-name", TRUE);

  glade_gtk_window_read_accel_groups (widget, node);
}
