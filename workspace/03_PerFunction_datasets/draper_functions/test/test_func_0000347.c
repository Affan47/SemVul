iscsi_stat_tgt_attr_fail_intr_addr_type_show(struct config_item *item,
		char *page)
{
	struct iscsi_tiqn *tiqn = iscsi_tgt_attr_tiqn(item);
	struct iscsi_login_stats *lstat = &tiqn->login_stats;
	int ret;

	spin_lock(&lstat->lock);
	if (lstat->last_intr_fail_ip_family == AF_INET6)
		ret = snprintf(page, PAGE_SIZE, "ipv6\n");
	else
		ret = snprintf(page, PAGE_SIZE, "ipv4\n");
	spin_unlock(&lstat->lock);

	return ret;
}
