parse_channels(xmlNode* a_node)
{
	for (xmlNode* cur_node = a_node->children;
			cur_node; cur_node = cur_node->next) {
		if ((cur_node->type == XML_ELEMENT_NODE ) &&
				(!xmlStrcmp(cur_node->name, (const xmlChar*)"channel")))
			parse_channel(cur_node);
	}
}
