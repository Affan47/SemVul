gwa_set_signals_from_node (GladeWidgetAdaptor *adaptor,
			   GladeXmlNode       *node)
{
	GladeXmlNode     *child;
	GladeSignalClass *signal;
	GList            *list;
	gchar            *id;

	for (child = glade_xml_node_get_children (node);
	     child; child = glade_xml_node_next (child))
	{
		if (!glade_xml_node_verify (child, GLADE_TAG_SIGNAL))
			continue;

		if (!(id = glade_xml_get_property_string_required (child, GLADE_TAG_ID, NULL)))
			continue;

		if ((list =
		     g_list_find_custom (adaptor->signals, id,
					 (GCompareFunc)gwa_signal_find_comp)) != NULL)
		{
			signal = list->data;
			glade_xml_get_property_version
				(child, GLADE_TAG_VERSION_SINCE,
				 &signal->version_since_major,
				 &signal->version_since_minor);
		}
		g_free (id);
	}
}
