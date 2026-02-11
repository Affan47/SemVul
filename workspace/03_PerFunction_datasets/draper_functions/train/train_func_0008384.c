target_scsi2_reservation_release(struct se_cmd *cmd)
{
	struct se_device *dev = cmd->se_dev;
	struct se_session *sess = cmd->se_sess;
	struct se_portal_group *tpg;
	int rc;

	if (!sess || !sess->se_tpg)
		goto out;
	rc = target_check_scsi2_reservation_conflict(cmd);
	if (rc == 1)
		goto out;
	if (rc < 0)
		return TCM_RESERVATION_CONFLICT;

	spin_lock(&dev->dev_reservation_lock);
	if (!dev->dev_reserved_node_acl || !sess)
		goto out_unlock;

	if (dev->dev_reserved_node_acl != sess->se_node_acl)
		goto out_unlock;

	if (dev->dev_res_bin_isid != sess->sess_bin_isid)
		goto out_unlock;

	dev->dev_reserved_node_acl = NULL;
	dev->dev_reservation_flags &= ~DRF_SPC2_RESERVATIONS;
	if (dev->dev_reservation_flags & DRF_SPC2_RESERVATIONS_WITH_ISID) {
		dev->dev_res_bin_isid = 0;
		dev->dev_reservation_flags &= ~DRF_SPC2_RESERVATIONS_WITH_ISID;
	}
	tpg = sess->se_tpg;
	pr_debug("SCSI-2 Released reservation for %s LUN: %llu ->"
		" MAPPED LUN: %llu for %s\n",
		tpg->se_tpg_tfo->get_fabric_name(),
		cmd->se_lun->unpacked_lun, cmd->orig_fe_lun,
		sess->se_node_acl->initiatorname);

out_unlock:
	spin_unlock(&dev->dev_reservation_lock);
out:
	target_complete_cmd(cmd, GOOD);
	return 0;
}
