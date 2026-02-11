ccss_selector_group_apply (ccss_selector_group_t const	*self,
			   ccss_node_t const		*node,
			   ccss_style_t			*style)
{
	traverse_apply_info_t info;

	g_assert (self && self->sets && style);

	info.type_name = NULL;
	info.node = node;
	info.style = style;
	info.ret = false;

	g_tree_foreach (self->sets, (GTraverseFunc) traverse_apply, &info);

	return info.ret;
}
