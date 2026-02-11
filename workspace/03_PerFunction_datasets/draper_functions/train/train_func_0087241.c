prepend_transform(xmlNodePtr node, char *transform)
{
	const xmlChar *attr = (xmlChar *) "transform";
	xmlChar *value = xmlGetProp(node, attr);
	if (NULL != value) {

		char * new_value = masprintf("%s %s",
			transform, (char *) value);
		xmlSetProp(node, attr, (xmlChar *) new_value);
		free(value);
		free(new_value);
	}
	else {

		xmlSetProp(node, attr, (xmlChar *) transform);
	}
}
