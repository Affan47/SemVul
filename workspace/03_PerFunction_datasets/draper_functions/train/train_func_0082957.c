xml_tree_destroy(XmlNode *node)
{
	const GSList	*iter;

	if(node != NULL)
	{
		for(iter = node->children; iter != NULL; iter = g_slist_next(iter))
			xml_tree_destroy(iter->data);
		xml_node_destroy(node);
	}
}
