xmldoc_get_syntax_cmd(struct ast_xml_node *fixnode, const char *name, int printname)
{
	struct ast_str *syntax;
	struct ast_xml_node *tmpnode, *node = fixnode;
	char *ret, *paramname;
	const char *paramtype, *attrname, *literal;
	int required, isenum, first = 1, isliteral;

	syntax = ast_str_create(128);
	if (!syntax) {

		return ast_strdup(name);
	}


	if (printname) {
		ast_str_append(&syntax, 0, "%s", name);
		first = 0;
	}

	for (node = ast_xml_node_get_children(node); node; node = ast_xml_node_get_next(node)) {
		if (strcasecmp(ast_xml_node_get_name(node), "parameter")) {
			continue;
		}

		if (xmldoc_has_inside(node, "parameter")) {

			paramname = xmldoc_get_syntax_cmd(node, "", 0);
			isenum = 1;
		} else {
			for (tmpnode = ast_xml_node_get_children(node); tmpnode; tmpnode = ast_xml_node_get_next(tmpnode)) {
				if (!strcasecmp(ast_xml_node_get_name(tmpnode), "enumlist")) {
					break;
				}
			}
			if (tmpnode) {


				paramname = xmldoc_parse_cmd_enumlist(tmpnode);
				isenum = 1;
			} else {

				attrname = ast_xml_get_attribute(node, "name");
				if (!attrname) {

					continue;
				}
				paramname = ast_strdup(attrname);
				ast_xml_free_attr(attrname);
				isenum = 0;
			}
		}


		required = 0;
		paramtype = ast_xml_get_attribute(node, "required");
		if (paramtype) {
			required = ast_true(paramtype);
			ast_xml_free_attr(paramtype);
		}


		isliteral = 0;
		literal = ast_xml_get_attribute(node, "literal");
		if (literal) {
			isliteral = ast_true(literal);
			ast_xml_free_attr(literal);
		}


		ast_str_append(&syntax, 0, "%s%s%s%s%s%s",
				(first ? "" : " "),
				(required ? "" : "["),
				(isenum || isliteral ? "" : "<"),
				paramname,
				(isenum || isliteral ? "" : ">"),
				(required ? "" : "]"));
		first = 0;
		ast_free(paramname);
	}


	ret = ast_strdup(ast_str_buffer(syntax));
	ast_free(syntax);

	return ret;
}
