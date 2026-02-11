unlink_obj(struct config_item *item)
{
	struct config_group *group;

	group = item->ci_group;
	if (group) {
		list_del_init(&item->ci_entry);

		item->ci_group = NULL;
		item->ci_parent = NULL;


		config_item_put(item);


		config_group_put(group);
	}
}
