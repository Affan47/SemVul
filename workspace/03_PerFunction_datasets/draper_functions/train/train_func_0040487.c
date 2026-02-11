sbp2_login(struct work_struct *work)
{
	struct sbp2_logical_unit *lu =
		container_of(work, struct sbp2_logical_unit, work.work);
	struct sbp2_target *tgt = lu->tgt;
	struct fw_device *device = target_parent_device(tgt);
	struct Scsi_Host *shost;
	struct scsi_device *sdev;
	struct sbp2_login_response response;
	int generation, node_id, local_node_id;

	if (fw_device_is_shutdown(device))
		return;

	generation    = device->generation;
	smp_rmb();
	node_id       = device->node_id;
	local_node_id = device->card->node_id;


	if (lu->has_sdev)
		sbp2_send_management_orb(lu, device->node_id, generation,
				SBP2_LOGOUT_REQUEST, lu->login_id, NULL);

	if (sbp2_send_management_orb(lu, node_id, generation,
				SBP2_LOGIN_REQUEST, lu->lun, &response) < 0) {
		if (lu->retries++ < 5) {
			sbp2_queue_work(lu, DIV_ROUND_UP(HZ, 5));
		} else {
			dev_err(tgt_dev(tgt), "failed to login to LUN %04x\n",
				lu->lun);

			sbp2_unblock(lu->tgt);
		}
		return;
	}

	tgt->node_id	  = node_id;
	tgt->address_high = local_node_id << 16;
	smp_wmb();
	lu->generation	  = generation;

	lu->command_block_agent_address =
		((u64)(be32_to_cpu(response.command_block_agent.high) & 0xffff)
		      << 32) | be32_to_cpu(response.command_block_agent.low);
	lu->login_id = be32_to_cpu(response.misc) & 0xffff;

	dev_notice(tgt_dev(tgt), "logged in to LUN %04x (%d retries)\n",
		   lu->lun, lu->retries);


	sbp2_set_busy_timeout(lu);

	lu->workfn = sbp2_reconnect;
	sbp2_agent_reset(lu);


	if (lu->has_sdev) {
		sbp2_cancel_orbs(lu);
		sbp2_conditionally_unblock(lu);

		return;
	}

	if (lu->tgt->workarounds & SBP2_WORKAROUND_DELAY_INQUIRY)
		ssleep(SBP2_INQUIRY_DELAY);

	shost = container_of((void *)tgt, struct Scsi_Host, hostdata[0]);
	sdev = __scsi_add_device(shost, 0, 0, sbp2_lun2int(lu->lun), lu);


	if (IS_ERR(sdev))
		goto out_logout_login;


	smp_rmb();
	if (generation != device->card->generation) {
		scsi_remove_device(sdev);
		scsi_device_put(sdev);
		goto out_logout_login;
	}


	lu->has_sdev = true;
	scsi_device_put(sdev);
	sbp2_allow_block(tgt);

	return;

 out_logout_login:
	smp_rmb();
	generation = device->generation;
	smp_rmb();

	sbp2_send_management_orb(lu, device->node_id, generation,
				 SBP2_LOGOUT_REQUEST, lu->login_id, NULL);


	lu->workfn = sbp2_login;
}
