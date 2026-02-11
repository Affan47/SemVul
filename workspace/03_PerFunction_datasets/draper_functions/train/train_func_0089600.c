core_tpg_check_initiator_node_acl(
	struct se_portal_group *tpg,
	unsigned char *initiatorname)
{
	struct se_node_acl *acl;

	acl = core_tpg_get_initiator_node_acl(tpg, initiatorname);
	if (acl)
		return acl;

	if (!tpg->se_tpg_tfo->tpg_check_demo_mode(tpg))
		return NULL;

	acl = target_alloc_node_acl(tpg, initiatorname);
	if (!acl)
		return NULL;


	kref_get(&acl->acl_kref);
	acl->dynamic_node_acl = 1;


	if ((tpg->se_tpg_tfo->tpg_check_demo_mode_login_only == NULL) ||
	    (tpg->se_tpg_tfo->tpg_check_demo_mode_login_only(tpg) != 1))
		core_tpg_add_node_to_devs(acl, tpg, NULL);

	target_add_node_acl(acl);
	return acl;
}
