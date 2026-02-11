target_tpg_has_node_acl(struct se_portal_group *tpg,
			     const char *initiatorname)
{
	struct se_node_acl *acl;
	bool found = false;

	mutex_lock(&tpg->acl_node_mutex);
	list_for_each_entry(acl, &tpg->acl_node_list, acl_list) {
		if (!strcmp(acl->initiatorname, initiatorname)) {
			found = true;
			break;
		}
	}
	mutex_unlock(&tpg->acl_node_mutex);

	return found;
}
