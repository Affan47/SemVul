vxml_node_is_named(const void *node, void *data)
{
	const xnode_t *xn = node;
	const char *name = data;

	return xnode_is_element(xn) && 0 == strcmp(name, xnode_element_name(xn));
}
