target_scsi2_reservation_reserve(struct se_cmd *cmd)
{
	struct se_device *dev = cmd->se_dev;
	struct se_session *sess = cmd->se_sess;
	struct se_portal_group *tpg;
	sense_reason_t ret = 0;
	int rc;

	if ((cmd->t_task_cdb[1] & 0x01) &&
	    (cmd->t_task_cdb[1] & 0x02)) {
		pr_err("LongIO and Obselete Bits set, returning"
				" ILLEGAL_REQUEST\n");
		return TCM_UNSUPPORTED_SCSI_OPCODE;
	}


	if (!sess || !sess->se_tpg)
		goto out;
	rc = target_check_scsi2_reservation_conflict(cmd);
	if (rc == 1)
		goto out;

	if (rc < 0)
		return TCM_RESERVATION_CONFLICT;

	tpg = sess->se_tpg;
	spin_lock(&dev->dev_reservation_lock);
	if (dev->dev_reserved_node_acl &&
	   (dev->dev_reserved_node_acl != sess->se_node_acl)) {
		pr_err("SCSI-2 RESERVATION CONFLIFT for %s fabric\n",
			tpg->se_tpg_tfo->get_fabric_name());
		pr_err("Original reserver LUN: %llu %s\n",
			cmd->se_lun->unpacked_lun,
			dev->dev_reserved_node_acl->initiatorname);
		pr_err("Current attempt - LUN: %llu -> MAPPED LUN: %llu"
			" from %s \n", cmd->se_lun->unpacked_lun,
			cmd->orig_fe_lun,
			sess->se_node_acl->initiatorname);
		ret = TCM_RESERVATION_CONFLICT;
		goto out_unlock;
	}

	dev->dev_reserved_node_acl = sess->se_node_acl;
	dev->dev_reservation_flags |= DRF_SPC2_RESERVATIONS;
	if (sess->sess_bin_isid != 0) {
		dev->dev_res_bin_isid = sess->sess_bin_isid;
		dev->dev_reservation_flags |= DRF_SPC2_RESERVATIONS_WITH_ISID;
	}
	pr_debug("SCSI-2 Reserved %s LUN: %llu -> MAPPED LUN: %llu"
		" for %s\n", tpg->se_tpg_tfo->get_fabric_name(),
		cmd->se_lun->unpacked_lun, cmd->orig_fe_lun,
		sess->se_node_acl->initiatorname);

out_unlock:
	spin_unlock(&dev->dev_reservation_lock);
out:
	if (!ret)
		target_complete_cmd(cmd, GOOD);
	return ret;
}
