iser_snd_completion(struct iser_tx_desc *tx_desc,
			struct ib_conn *ib_conn)
{
	struct iscsi_task *task;
	struct iser_device *device = ib_conn->device;

	if (tx_desc->type == ISCSI_TX_DATAOUT) {
		ib_dma_unmap_single(device->ib_device, tx_desc->dma_addr,
					ISER_HEADERS_LEN, DMA_TO_DEVICE);
		kmem_cache_free(ig.desc_cache, tx_desc);
		tx_desc = NULL;
	}

	if (tx_desc && tx_desc->type == ISCSI_TX_CONTROL) {

		task = (void *) ((long)(void *)tx_desc -
				  sizeof(struct iscsi_task));
		if (task->hdr->itt == RESERVED_ITT)
			iscsi_put_task(task);
	}
}
