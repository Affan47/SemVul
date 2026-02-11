ast_xml_open(char *filename)
{
	xmlDoc *doc;

	if (!filename) {
		return NULL;
	}

	doc = xmlReadFile(filename, NULL, XML_PARSE_RECOVER);
	if (doc) {

		if (xmlXIncludeProcess(doc) < 0) {
			xmlFreeDoc(doc);
			return NULL;
		}
	}

	return (struct ast_xml_doc *) doc;
}
