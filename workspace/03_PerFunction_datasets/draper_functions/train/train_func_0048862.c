beiscsi_eh_device_reset(struct scsi_cmnd *sc)
{
	struct iscsi_task *abrt_task;
	struct beiscsi_io_task *abrt_io_task;
	struct iscsi_conn *conn;
	struct beiscsi_conn *beiscsi_conn;
	struct beiscsi_hba *phba;
	struct iscsi_session *session;
	struct iscsi_cls_session *cls_session;
	struct invalidate_command_table *inv_tbl;
	struct be_dma_mem nonemb_cmd;
	unsigned int cid, tag, i, num_invalidate;
	int rc;


	cls_session = starget_to_session(scsi_target(sc->device));
	session = cls_session->dd_data;
	spin_lock_bh(&session->lock);
	if (!session->leadconn || session->state != ISCSI_STATE_LOGGED_IN) {
		spin_unlock_bh(&session->lock);
		return FAILED;
	}
	conn = session->leadconn;
	beiscsi_conn = conn->dd_data;
	phba = beiscsi_conn->phba;
	cid = beiscsi_conn->beiscsi_conn_cid;
	inv_tbl = phba->inv_tbl;
	memset(inv_tbl, 0x0, sizeof(*inv_tbl) * BE2_CMDS_PER_CXN);
	num_invalidate = 0;
	for (i = 0; i < conn->session->cmds_max; i++) {
		abrt_task = conn->session->cmds[i];
		abrt_io_task = abrt_task->dd_data;
		if (!abrt_task->sc || abrt_task->state == ISCSI_TASK_FREE)
			continue;

		if (sc->device->lun != abrt_task->sc->device->lun)
			continue;


		AMAP_SET_BITS(struct amap_iscsi_wrb, invld,
			      abrt_io_task->pwrb_handle->pwrb,
			      1);

		inv_tbl->cid = cid;
		inv_tbl->icd = abrt_io_task->psgl_handle->sgl_index;
		num_invalidate++;
		inv_tbl++;
	}
	spin_unlock_bh(&session->lock);
	inv_tbl = phba->inv_tbl;

	nonemb_cmd.va = pci_alloc_consistent(phba->ctrl.pdev,
				sizeof(struct invalidate_commands_params_in),
				&nonemb_cmd.dma);
	if (nonemb_cmd.va == NULL) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_EH,
			    "BM_%d : Failed to allocate memory for"
			    "mgmt_invalidate_icds\n");
		return FAILED;
	}
	nonemb_cmd.size = sizeof(struct invalidate_commands_params_in);
	memset(nonemb_cmd.va, 0, nonemb_cmd.size);
	tag = mgmt_invalidate_icds(phba, inv_tbl, num_invalidate,
				   cid, &nonemb_cmd);
	if (!tag) {
		beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_EH,
			    "BM_%d : mgmt_invalidate_icds could not be"
			    " submitted\n");
		pci_free_consistent(phba->ctrl.pdev, nonemb_cmd.size,
				    nonemb_cmd.va, nonemb_cmd.dma);
		return FAILED;
	}

	rc = beiscsi_mccq_compl(phba, tag, NULL, &nonemb_cmd);
	if (rc != -EBUSY)
		pci_free_consistent(phba->ctrl.pdev, nonemb_cmd.size,
				    nonemb_cmd.va, nonemb_cmd.dma);
	return iscsi_eh_device_reset(sc);
}
