search_xml_node_is_empty(void *node, void *data)
{
	xnode_t *xn = node;
	bool *empty = data;

	if (!*empty)
		return;

	if (xnode_is_comment(xn))
		return;

	if (xnode_is_text(xn) && strlen(xnode_text(xn)) > 0) {
		*empty = FALSE;
	} else if (xnode_prop_count(xn) > 0) {
		*empty = FALSE;
	}
}
