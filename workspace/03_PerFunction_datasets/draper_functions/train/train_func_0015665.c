beiscsi_cleanup_task(struct iscsi_task *task)
{
	struct beiscsi_io_task *io_task = task->dd_data;
	struct iscsi_conn *conn = task->conn;
	struct beiscsi_conn *beiscsi_conn = conn->dd_data;
	struct beiscsi_hba *phba = beiscsi_conn->phba;
	struct beiscsi_session *beiscsi_sess = beiscsi_conn->beiscsi_sess;
	struct hwi_wrb_context *pwrb_context;
	struct hwi_controller *phwi_ctrlr;
	uint16_t cri_index = BE_GET_CRI_FROM_CID(
			     beiscsi_conn->beiscsi_conn_cid);

	phwi_ctrlr = phba->phwi_ctrlr;
	pwrb_context = &phwi_ctrlr->wrb_context[cri_index];

	if (io_task->cmd_bhs) {
		pci_pool_free(beiscsi_sess->bhs_pool, io_task->cmd_bhs,
			      io_task->bhs_pa.u.a64.address);
		io_task->cmd_bhs = NULL;
	}

	if (task->sc) {
		if (io_task->pwrb_handle) {
			free_wrb_handle(phba, pwrb_context,
					io_task->pwrb_handle);
			io_task->pwrb_handle = NULL;
		}

		if (io_task->psgl_handle) {
			spin_lock(&phba->io_sgl_lock);
			free_io_sgl_handle(phba, io_task->psgl_handle);
			spin_unlock(&phba->io_sgl_lock);
			io_task->psgl_handle = NULL;
		}

		if (io_task->scsi_cmnd) {
			scsi_dma_unmap(io_task->scsi_cmnd);
			io_task->scsi_cmnd = NULL;
		}
	} else {
		if (!beiscsi_conn->login_in_progress)
			beiscsi_free_mgmt_task_handles(beiscsi_conn, task);
	}
}
