named_item(const std::string &name) const
{
	CL_DomNode node = get_first_child();
	while (node.is_null() == false)
	{
		if (node.get_node_name() == name) return node;
		node = node.get_next_sibling();
	}
	return CL_DomNode();
}
