glade_gtk_widget_write_atk_action (GladeProperty      *property,
				   GladeXmlContext    *context,
				   GladeXmlNode       *node)
{
 	GladeProjectFormat fmt;
	GladeXmlNode *prop_node;
	gchar        *value = NULL;

	fmt = glade_project_get_format (property->widget->project);

	glade_property_get (property, &value);

	if (value && value[0])
	{
		prop_node = glade_xml_node_new (context, GLADE_TAG_A11Y_ACTION (fmt));
		glade_xml_node_append_child (node, prop_node);

		glade_xml_node_set_property_string (prop_node,
						    GLADE_TAG_A11Y_ACTION_NAME,
						    &property->klass->id[4]);
		glade_xml_node_set_property_string (prop_node,
						    GLADE_TAG_A11Y_DESC,
						    value);
	}
}
