ast_xml_read_memory(char *buffer, size_t size)
{
	xmlDoc *doc;

	if (!buffer) {
		return NULL;
	}

	if (!(doc = xmlParseMemory(buffer, (int) size))) {

		if (xmlXIncludeProcess(doc) < 0) {
			xmlFreeDoc(doc);
			return NULL;
		}
	}

	return (struct ast_xml_doc *) doc;
}
