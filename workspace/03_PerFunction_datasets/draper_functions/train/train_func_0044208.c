ccss_selector_group_apply_type (ccss_selector_group_t const	*self,
			       char const			*type_name,
			       ccss_style_t			*style)
{
	traverse_apply_info_t info;

	g_assert (self && self->sets && style);

	info.type_name = type_name;
	info.node = NULL;
	info.style = style;
	info.ret = false;

	g_tree_foreach (self->sets, (GTraverseFunc) traverse_apply, &info);

	return info.ret;
}
