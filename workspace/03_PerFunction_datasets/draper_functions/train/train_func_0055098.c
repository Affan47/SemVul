tcm_loop_tpg_nexus_show(struct config_item *item, char *page)
{
	struct se_portal_group *se_tpg = to_tpg(item);
	struct tcm_loop_tpg *tl_tpg = container_of(se_tpg,
			struct tcm_loop_tpg, tl_se_tpg);
	struct tcm_loop_nexus *tl_nexus;
	ssize_t ret;

	tl_nexus = tl_tpg->tl_nexus;
	if (!tl_nexus)
		return -ENODEV;

	ret = snprintf(page, PAGE_SIZE, "%s\n",
		tl_nexus->se_sess->se_node_acl->initiatorname);

	return ret;
}
