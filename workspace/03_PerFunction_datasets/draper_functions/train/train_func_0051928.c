add_construct_glade (char * file, char * root, char * domain)
{
	Node *var;
	Type * type;

	type = (Type *)node_new (TYPE_NODE,
				 "name", "GladeXML",
				 "pointer", "*",
				 NULL);
	initializer = g_strdup_printf("\t{\n"
				      "\tGtkWidget * root;\n"
				      "\t%%1$s->_priv->_glade_xml = glade_xml_new(%s, %s, %s);\n"
				      "\troot = glade_xml_get_widget(%%1$s->_priv->_glade_xml, %s);\n"
				      "\tgtk_widget_show(root);\n"
				      "\tgtk_container_add(GTK_CONTAINER(%%1$s), root);\n"
				      "\tglade_xml_signal_autoconnect_full(%%1$s->_priv->_glade_xml, (GladeXMLConnectFunc)___glade_xml_connect_foreach, (gpointer)%%1$s);\n"
				      "}\n", file, root, domain ? domain : "NULL", root);

	var = node_new (VARIABLE_NODE,
			"scope", PRIVATE_SCOPE,
			"vtype:steal", type,
			"glade_widget", FALSE,
			"id:steal", "_glade_xml",
			"destructor_unref", FALSE,
			"destructor", "g_object_unref",
			"destructor_simple", TRUE,
			"initializer", initializer,
			"initializer_simple", FALSE,
			NULL);
	class_nodes = g_list_prepend(class_nodes, var);
}
