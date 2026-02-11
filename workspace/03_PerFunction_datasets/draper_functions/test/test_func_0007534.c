glade_project_count_xml_objects (GladeProject *project, GladeXmlNode *root, gint count)
{
	GladeXmlNode    *node;

	for (node = glade_xml_node_get_children (root);
	     node; node = glade_xml_node_next (node))
	{
		if (glade_xml_node_verify_silent
		    (node, GLADE_XML_TAG_WIDGET (project->priv->format)))
			count = glade_project_count_xml_objects (project, node, ++count);
		else if (glade_xml_node_verify_silent (node, GLADE_XML_TAG_CHILD))
			count = glade_project_count_xml_objects (project, node, count);
	}
	return count;
}
