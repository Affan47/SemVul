core_dev_free_initiator_node_lun_acl(
	struct se_portal_group *tpg,
	struct se_lun_acl *lacl)
{
	pr_debug("%s_TPG[%hu] - Freeing ACL for %s InitiatorNode: %s"
		" Mapped LUN: %llu\n", tpg->se_tpg_tfo->get_fabric_name(),
		tpg->se_tpg_tfo->tpg_get_tag(tpg),
		tpg->se_tpg_tfo->get_fabric_name(),
		lacl->se_lun_nacl->initiatorname, lacl->mapped_lun);

	kfree(lacl);
}
