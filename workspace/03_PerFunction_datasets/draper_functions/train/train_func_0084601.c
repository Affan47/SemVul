iscsit_tpg_del_portal_group(
	struct iscsi_tiqn *tiqn,
	struct iscsi_portal_group *tpg,
	int force)
{
	u8 old_state = tpg->tpg_state;

	spin_lock(&tpg->tpg_state_lock);
	tpg->tpg_state = TPG_STATE_INACTIVE;
	spin_unlock(&tpg->tpg_state_lock);

	if (iscsit_release_sessions_for_tpg(tpg, force) < 0) {
		pr_err("Unable to delete iSCSI Target Portal Group:"
			" %hu while active sessions exist, and force=0\n",
			tpg->tpgt);
		tpg->tpg_state = old_state;
		return -EPERM;
	}

	if (tpg->param_list) {
		iscsi_release_param_list(tpg->param_list);
		tpg->param_list = NULL;
	}

	core_tpg_deregister(&tpg->tpg_se_tpg);

	spin_lock(&tpg->tpg_state_lock);
	tpg->tpg_state = TPG_STATE_FREE;
	spin_unlock(&tpg->tpg_state_lock);

	spin_lock(&tiqn->tiqn_tpg_lock);
	tiqn->tiqn_ntpgs--;
	list_del(&tpg->tpg_list);
	spin_unlock(&tiqn->tiqn_tpg_lock);

	pr_debug("CORE[%s]_TPG[%hu] - Deleted iSCSI Target Portal Group\n",
			tiqn->tiqn, tpg->tpgt);

	kfree(tpg);
	return 0;
}
