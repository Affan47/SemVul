beiscsi_free_mgmt_task_handles(struct beiscsi_conn *beiscsi_conn,
				struct iscsi_task *task)
{
	struct beiscsi_io_task *io_task;
	struct beiscsi_hba *phba = beiscsi_conn->phba;
	struct hwi_wrb_context *pwrb_context;
	struct hwi_controller *phwi_ctrlr;
	uint16_t cri_index = BE_GET_CRI_FROM_CID(
				beiscsi_conn->beiscsi_conn_cid);

	phwi_ctrlr = phba->phwi_ctrlr;
	pwrb_context = &phwi_ctrlr->wrb_context[cri_index];

	io_task = task->dd_data;

	if (io_task->pwrb_handle) {
		memset(io_task->pwrb_handle->pwrb, 0,
		       sizeof(struct iscsi_wrb));
		free_wrb_handle(phba, pwrb_context,
				io_task->pwrb_handle);
		io_task->pwrb_handle = NULL;
	}

	if (io_task->psgl_handle) {
		spin_lock_bh(&phba->mgmt_sgl_lock);
		free_mgmt_sgl_handle(phba,
				     io_task->psgl_handle);
		io_task->psgl_handle = NULL;
		spin_unlock_bh(&phba->mgmt_sgl_lock);
	}

	if (io_task->mtask_addr) {
		pci_unmap_single(phba->pcidev,
				 io_task->mtask_addr,
				 io_task->mtask_data_count,
				 PCI_DMA_TODEVICE);
		io_task->mtask_addr = 0;
	}
}
