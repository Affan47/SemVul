xmldoc_parse_info(struct ast_xml_node *node, const char *tabs, const char *posttabs, struct ast_str **buffer)
{
	const char *tech;
	char *internaltabs;
	int internal_ret;
	int ret = 0;

	if (strcasecmp(ast_xml_node_get_name(node), "info")) {
		return ret;
	}

	ast_asprintf(&internaltabs, "%s    ", tabs);
	if (!internaltabs) {
		return ret;
	}

	tech = ast_xml_get_attribute(node, "tech");
	if (tech) {
		ast_str_append(buffer, 0, "%s<note>Technology: %s</note>\n", internaltabs, tech);
		ast_xml_free_attr(tech);
	}

	ret = 1;

	for (node = ast_xml_node_get_children(node); node; node = ast_xml_node_get_next(node)) {
		if (!strcasecmp(ast_xml_node_get_name(node), "enumlist")) {
			xmldoc_parse_enumlist(node, internaltabs, buffer);
		} else if ((internal_ret = xmldoc_parse_common_elements(node, internaltabs, posttabs, buffer))) {
			if (internal_ret > ret) {
				ret = internal_ret;
			}
		}
	}
	ast_free(internaltabs);

	return ret;
}
