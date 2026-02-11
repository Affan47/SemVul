get_node_phandle(struct node *root, struct node *node)
{
	static cell_t phandle = 1;

	if ((node->phandle != 0) && (node->phandle != -1))
		return node->phandle;

	while (get_node_by_phandle(root, phandle))
		phandle++;

	node->phandle = phandle;

	if (!get_property(node, "linux,phandle")
	    && (phandle_format & PHANDLE_LEGACY))
		add_property(node,
			     build_property("linux,phandle",
					    data_append_cell(empty_data, phandle)));

	if (!get_property(node, "phandle")
	    && (phandle_format & PHANDLE_EPAPR))
		add_property(node,
			     build_property("phandle",
					    data_append_cell(empty_data, phandle)));


	return node->phandle;
}
