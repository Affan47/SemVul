get_self_element(VXnode& vnode) {
	xmlNode& node=vnode.get_xmlnode();

	if(node.type!=XML_ELEMENT_NODE)
		throw Exception(PARSER_RUNTIME,
			0,
			"method can only be called on nodes of ELEMENT type");

	return node;
}
