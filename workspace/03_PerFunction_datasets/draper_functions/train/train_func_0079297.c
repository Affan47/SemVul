srp_reset_device(struct scsi_cmnd *scmnd)
{
	struct srp_target_port *target = host_to_target(scmnd->device->host);
	struct srp_rdma_ch *ch;
	int i;
	u8 status;

	shost_printk(KERN_ERR, target->scsi_host, "SRP reset_device called\n");

	ch = &target->ch[0];
	if (srp_send_tsk_mgmt(ch, SRP_TAG_NO_REQ, scmnd->device->lun,
			      SRP_TSK_LUN_RESET, &status))
		return FAILED;
	if (status)
		return FAILED;

	for (i = 0; i < target->ch_count; i++) {
		ch = &target->ch[i];
		for (i = 0; i < target->req_ring_size; ++i) {
			struct srp_request *req = &ch->req_ring[i];

			srp_finish_req(ch, req, scmnd->device, DID_RESET << 16);
		}
	}

	return SUCCESS;
}
