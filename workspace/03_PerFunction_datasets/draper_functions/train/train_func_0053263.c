sbp_tpg_directory_id_show(struct config_item *item, char *page)
{
	struct se_portal_group *se_tpg = to_tpg(item);
	struct sbp_tpg *tpg = container_of(se_tpg, struct sbp_tpg, se_tpg);
	struct sbp_tport *tport = tpg->tport;

	if (tport->directory_id == -1)
		return sprintf(page, "implicit\n");
	else
		return sprintf(page, "%06x\n", tport->directory_id);
}
