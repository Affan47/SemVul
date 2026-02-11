dm_tree_next_child(void **handle,
					const struct dm_tree_node *parent,
					uint32_t inverted)
{
	struct dm_list **dlink = (struct dm_list **) handle;
	const struct dm_list *use_list;

	if (inverted)
		use_list = &parent->used_by;
	else
		use_list = &parent->uses;

	if (!*dlink)
		*dlink = dm_list_first(use_list);
	else
		*dlink = dm_list_next(use_list, *dlink);

	return (*dlink) ? dm_list_item(*dlink, struct dm_tree_link)->node : NULL;
}
