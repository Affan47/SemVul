sci_io_request_construct_sata(struct isci_request *ireq,
			       u32 len,
			       enum dma_data_direction dir,
			       bool copy)
{
	enum sci_status status = SCI_SUCCESS;
	struct sas_task *task = isci_request_access_task(ireq);
	struct domain_device *dev = ireq->target_device->domain_dev;


	if (test_bit(IREQ_TMF, &ireq->flags)) {
		struct isci_tmf *tmf = isci_request_access_tmf(ireq);

		dev_err(&ireq->owning_controller->pdev->dev,
			"%s: Request 0x%p received un-handled SAT "
			"management protocol 0x%x.\n",
			__func__, ireq, tmf->tmf_code);

		return SCI_FAILURE;
	}

	if (!sas_protocol_ata(task->task_proto)) {
		dev_err(&ireq->owning_controller->pdev->dev,
			"%s: Non-ATA protocol in SATA path: 0x%x\n",
			__func__,
			task->task_proto);
		return SCI_FAILURE;

	}


	if (dev->sata_dev.class == ATA_DEV_ATAPI &&
	    task->ata_task.fis.command == ATA_CMD_PACKET) {
		sci_atapi_construct(ireq);
		return SCI_SUCCESS;
	}


	if (task->data_dir == DMA_NONE) {
		scu_stp_raw_request_construct_task_context(ireq);
		return SCI_SUCCESS;
	}


	if (task->ata_task.use_ncq) {
		sci_stp_optimized_request_construct(ireq,
							 SCU_TASK_TYPE_FPDMAQ_READ,
							 len, dir);
		return SCI_SUCCESS;
	}


	if (task->ata_task.dma_xfer) {
		sci_stp_optimized_request_construct(ireq,
							 SCU_TASK_TYPE_DMA_IN,
							 len, dir);
		return SCI_SUCCESS;
	} else
		return sci_stp_pio_request_construct(ireq, copy);

	return status;
}
