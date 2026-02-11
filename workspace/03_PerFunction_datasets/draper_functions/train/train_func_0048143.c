bnx2i_session_create(struct iscsi_endpoint *ep,
		     uint16_t cmds_max, uint16_t qdepth,
		     uint32_t initial_cmdsn)
{
	struct Scsi_Host *shost;
	struct iscsi_cls_session *cls_session;
	struct bnx2i_hba *hba;
	struct bnx2i_endpoint *bnx2i_ep;

	if (!ep) {
		printk(KERN_ERR "bnx2i: missing ep.\n");
		return NULL;
	}

	bnx2i_ep = ep->dd_data;
	shost = bnx2i_ep->hba->shost;
	hba = iscsi_host_priv(shost);
	if (bnx2i_adapter_ready(hba))
		return NULL;


	if (cmds_max > hba->max_sqes)
		cmds_max = hba->max_sqes;
	else if (cmds_max < BNX2I_SQ_WQES_MIN)
		cmds_max = BNX2I_SQ_WQES_MIN;

	cls_session = iscsi_session_setup(&bnx2i_iscsi_transport, shost,
					  cmds_max, 0, sizeof(struct bnx2i_cmd),
					  initial_cmdsn, ISCSI_MAX_TARGET);
	if (!cls_session)
		return NULL;

	if (bnx2i_setup_cmd_pool(hba, cls_session->dd_data))
		goto session_teardown;
	return cls_session;

session_teardown:
	iscsi_session_teardown(cls_session);
	return NULL;
}
