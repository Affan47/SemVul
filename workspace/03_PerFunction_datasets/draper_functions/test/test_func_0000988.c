tcm_qla2xxx_npiv_tpg_enable_store(struct config_item *item,
		const char *page, size_t count)
{
	struct se_portal_group *se_tpg = to_tpg(item);
	struct se_wwn *se_wwn = se_tpg->se_tpg_wwn;
	struct tcm_qla2xxx_lport *lport = container_of(se_wwn,
			struct tcm_qla2xxx_lport, lport_wwn);
	struct scsi_qla_host *vha = lport->qla_vha;
	struct tcm_qla2xxx_tpg *tpg = container_of(se_tpg,
			struct tcm_qla2xxx_tpg, se_tpg);
	unsigned long op;
	int rc;

	rc = kstrtoul(page, 0, &op);
	if (rc < 0) {
		pr_err("kstrtoul() returned %d\n", rc);
		return -EINVAL;
	}
	if ((op != 1) && (op != 0)) {
		pr_err("Illegal value for tpg_enable: %lu\n", op);
		return -EINVAL;
	}
	if (op) {
		if (atomic_read(&tpg->lport_tpg_enabled))
			return -EEXIST;

		atomic_set(&tpg->lport_tpg_enabled, 1);
		qlt_enable_vha(vha);
	} else {
		if (!atomic_read(&tpg->lport_tpg_enabled))
			return count;

		atomic_set(&tpg->lport_tpg_enabled, 0);
		qlt_stop_phase1(vha->vha_tgt.qla_tgt);
	}

	return count;
}
