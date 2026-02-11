qla4xxx_mem_alloc(struct scsi_qla_host *ha)
{
	unsigned long align;


	ha->queues_len = ((REQUEST_QUEUE_DEPTH * QUEUE_SIZE) +
			  (RESPONSE_QUEUE_DEPTH * QUEUE_SIZE) +
			  sizeof(struct shadow_regs) +
			  MEM_ALIGN_VALUE +
			  (PAGE_SIZE - 1)) & ~(PAGE_SIZE - 1);
	ha->queues = dma_alloc_coherent(&ha->pdev->dev, ha->queues_len,
					&ha->queues_dma, GFP_KERNEL);
	if (ha->queues == NULL) {
		ql4_printk(KERN_WARNING, ha,
		    "Memory Allocation failed - queues.\n");

		goto mem_alloc_error_exit;
	}
	memset(ha->queues, 0, ha->queues_len);


	align = 0;
	if ((unsigned long)ha->queues_dma & (MEM_ALIGN_VALUE - 1))
		align = MEM_ALIGN_VALUE - ((unsigned long)ha->queues_dma &
					   (MEM_ALIGN_VALUE - 1));


	ha->request_dma = ha->queues_dma + align;
	ha->request_ring = (struct queue_entry *) (ha->queues + align);
	ha->response_dma = ha->queues_dma + align +
		(REQUEST_QUEUE_DEPTH * QUEUE_SIZE);
	ha->response_ring = (struct queue_entry *) (ha->queues + align +
						    (REQUEST_QUEUE_DEPTH *
						     QUEUE_SIZE));
	ha->shadow_regs_dma = ha->queues_dma + align +
		(REQUEST_QUEUE_DEPTH * QUEUE_SIZE) +
		(RESPONSE_QUEUE_DEPTH * QUEUE_SIZE);
	ha->shadow_regs = (struct shadow_regs *) (ha->queues + align +
						  (REQUEST_QUEUE_DEPTH *
						   QUEUE_SIZE) +
						  (RESPONSE_QUEUE_DEPTH *
						   QUEUE_SIZE));


	ha->srb_mempool = mempool_create(SRB_MIN_REQ, mempool_alloc_slab,
					 mempool_free_slab, srb_cachep);
	if (ha->srb_mempool == NULL) {
		ql4_printk(KERN_WARNING, ha,
		    "Memory Allocation failed - SRB Pool.\n");

		goto mem_alloc_error_exit;
	}

	ha->chap_dma_pool = dma_pool_create("ql4_chap", &ha->pdev->dev,
					    CHAP_DMA_BLOCK_SIZE, 8, 0);

	if (ha->chap_dma_pool == NULL) {
		ql4_printk(KERN_WARNING, ha,
		    "%s: chap_dma_pool allocation failed..\n", __func__);
		goto mem_alloc_error_exit;
	}

	ha->fw_ddb_dma_pool = dma_pool_create("ql4_fw_ddb", &ha->pdev->dev,
					      DDB_DMA_BLOCK_SIZE, 8, 0);

	if (ha->fw_ddb_dma_pool == NULL) {
		ql4_printk(KERN_WARNING, ha,
			   "%s: fw_ddb_dma_pool allocation failed..\n",
			   __func__);
		goto mem_alloc_error_exit;
	}

	return QLA_SUCCESS;

mem_alloc_error_exit:
	qla4xxx_mem_free(ha);
	return QLA_ERROR;
}
