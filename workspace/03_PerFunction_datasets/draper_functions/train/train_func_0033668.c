drop_space(struct config_group *g, struct config_item *i)
{
	struct dlm_space *sp = config_item_to_space(i);
	struct config_item *tmp;
	int j;


	for (j = 0; sp->group.default_groups[j]; j++) {
		tmp = &sp->group.default_groups[j]->cg_item;
		sp->group.default_groups[j] = NULL;
		config_item_put(tmp);
	}

	config_item_put(i);
}
