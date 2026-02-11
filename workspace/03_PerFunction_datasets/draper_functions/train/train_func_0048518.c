dev_set_preferred_name(struct str_list *sl, struct device *dev)
{


	if (_cache.preferred_names_matcher)
		return;

	log_debug("%s: New preferred name", sl->str);
	dm_list_del(&sl->list);
	dm_list_add_h(&dev->aliases, &sl->list);
}
