_qualify_namespace(XML_Parser parser, const xmlChar *name, const xmlChar *URI, xmlChar **qualified)
{
	if (URI) {

			*qualified = xmlStrdup(URI);
			*qualified = xmlStrncat(*qualified, parser->_ns_seperator, 1);
			*qualified = xmlStrncat(*qualified, name, xmlStrlen(name));
	} else {
		*qualified = xmlStrdup(name);
	}
}
