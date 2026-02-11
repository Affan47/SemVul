e_filter_part_xml_encode (EFilterPart *part)
{
	xmlNodePtr node;
	GList *link;

	g_return_val_if_fail (E_IS_FILTER_PART (part), NULL);

	node = xmlNewNode (NULL, (xmlChar *)"part");
	xmlSetProp (node, (xmlChar *)"name", (xmlChar *) part->name);

	for (link = part->elements; link != NULL; link = g_list_next (link)) {
		EFilterElement *element = link->data;
		xmlNodePtr value;

		value = e_filter_element_xml_encode (element);
		xmlAddChild (node, value);
	}

	return node;
}
