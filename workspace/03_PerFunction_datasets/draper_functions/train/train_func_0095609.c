register_config_options(config_option_t *opt, UINTN n, config_option_group_scope_t group)
{
	config_option_group_t *newgrp, **grp;

	if (opt == NULL || n == 0 || (group != OPTIONS_GROUP_GLOBAL && group != OPTIONS_GROUP_IMAGE)) return -1;

	VERB_PRT(3, Print(L"registering %d options for group %s\n", n, group == OPTIONS_GROUP_GLOBAL ? L"global" : L"image"));

	newgrp = alloc(sizeof(config_option_group_t), EfiLoaderData);
	if (newgrp == NULL) return -1;

	grp = group == OPTIONS_GROUP_GLOBAL ? &global_option_list : &image_option_list;

	if (*grp) while ((*grp)->next) grp = &(*grp)->next;

	newgrp->options  = opt;
	newgrp->next     = NULL;
	newgrp->nentries = n;

	if (*grp) {
		(*grp)->next = newgrp;
	} else {
		*grp = newgrp;
	}
	return 0;
}
