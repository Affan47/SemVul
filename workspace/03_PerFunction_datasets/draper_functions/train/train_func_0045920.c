tcm_loop_tpg_transport_status_show(struct config_item *item,
		char *page)
{
	struct se_portal_group *se_tpg = to_tpg(item);
	struct tcm_loop_tpg *tl_tpg = container_of(se_tpg,
			struct tcm_loop_tpg, tl_se_tpg);
	const char *status = NULL;
	ssize_t ret = -EINVAL;

	switch (tl_tpg->tl_transport_status) {
	case TCM_TRANSPORT_ONLINE:
		status = "online";
		break;
	case TCM_TRANSPORT_OFFLINE:
		status = "offline";
		break;
	default:
		break;
	}

	if (status)
		ret = snprintf(page, PAGE_SIZE, "%s\n", status);

	return ret;
}
