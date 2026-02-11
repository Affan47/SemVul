v4l2_of_parse_link(const struct device_node *node,
		       struct v4l2_of_link *link)
{
	struct device_node *np;

	memset(link, 0, sizeof(*link));

	np = of_get_parent(node);
	of_property_read_u32(np, "reg", &link->local_port);
	np = of_get_next_parent(np);
	if (of_node_cmp(np->name, "ports") == 0)
		np = of_get_next_parent(np);
	link->local_node = np;

	np = of_parse_phandle(node, "remote-endpoint", 0);
	if (!np) {
		of_node_put(link->local_node);
		return -ENOLINK;
	}

	np = of_get_parent(np);
	of_property_read_u32(np, "reg", &link->remote_port);
	np = of_get_next_parent(np);
	if (of_node_cmp(np->name, "ports") == 0)
		np = of_get_next_parent(np);
	link->remote_node = np;

	return 0;
}
