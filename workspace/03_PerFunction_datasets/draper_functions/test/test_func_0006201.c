xps_parse_document_structure(xps_document *doc, xml_element *root)
{
	xml_element *node;
	if (!strcmp(xml_tag(root), "DocumentStructure"))
	{
		node = xml_down(root);
		if (!strcmp(xml_tag(node), "DocumentStructure.Outline"))
		{
			node = xml_down(node);
			if (!strcmp(xml_tag(node), "DocumentOutline"))
				return xps_parse_document_outline(doc, node);
		}
	}
	return NULL;
}
