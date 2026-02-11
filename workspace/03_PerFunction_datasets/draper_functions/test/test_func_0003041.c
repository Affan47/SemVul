target_fabric_mappedlun_write_protect_show(
		struct config_item *item, char *page)
{
	struct se_lun_acl *lacl = item_to_lun_acl(item);
	struct se_node_acl *se_nacl = lacl->se_lun_nacl;
	struct se_dev_entry *deve;
	ssize_t len = 0;

	rcu_read_lock();
	deve = target_nacl_find_deve(se_nacl, lacl->mapped_lun);
	if (deve) {
		len = sprintf(page, "%d\n",
			(deve->lun_flags & TRANSPORT_LUNFLAGS_READ_ONLY) ? 1 : 0);
	}
	rcu_read_unlock();

	return len;
}
