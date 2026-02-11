glade_gtk_parse_atk_props_gtkbuilder (GladeWidget  *widget,
				      GladeXmlNode *node)
{
	GladeXmlNode *child, *object_node;
	gchar        *internal;


	for (child = glade_xml_node_get_children (node);
	     child; child = glade_xml_node_next (child))
	{
		if (glade_xml_node_verify_silent (child, GLADE_XML_TAG_CHILD))
		{
			if ((internal =
			     glade_xml_get_property_string (child, GLADE_XML_TAG_INTERNAL_CHILD)))
			{
				if (!strcmp (internal, GLADE_TAG_A11Y_INTERNAL_NAME) &&
				    (object_node =
				     glade_xml_search_child_required
				     (child, GLADE_XML_TAG_BUILDER_WIDGET)))
					glade_gtk_parse_atk_props (widget, object_node);

				g_free (internal);
			}
		}
	}
}
