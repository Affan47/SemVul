efx_ef10_rx_init(struct efx_rx_queue *rx_queue)
{
	MCDI_DECLARE_BUF(inbuf,
			 MC_CMD_INIT_RXQ_IN_LEN(EFX_MAX_DMAQ_SIZE * 8 /
						EFX_BUF_SIZE));
	struct efx_channel *channel = efx_rx_queue_channel(rx_queue);
	size_t entries = rx_queue->rxd.buf.len / EFX_BUF_SIZE;
	struct efx_nic *efx = rx_queue->efx;
	struct efx_ef10_nic_data *nic_data = efx->nic_data;
	size_t inlen;
	dma_addr_t dma_addr;
	int rc;
	int i;
	BUILD_BUG_ON(MC_CMD_INIT_RXQ_OUT_LEN != 0);

	rx_queue->scatter_n = 0;
	rx_queue->scatter_len = 0;

	MCDI_SET_DWORD(inbuf, INIT_RXQ_IN_SIZE, rx_queue->ptr_mask + 1);
	MCDI_SET_DWORD(inbuf, INIT_RXQ_IN_TARGET_EVQ, channel->channel);
	MCDI_SET_DWORD(inbuf, INIT_RXQ_IN_LABEL, efx_rx_queue_index(rx_queue));
	MCDI_SET_DWORD(inbuf, INIT_RXQ_IN_INSTANCE,
		       efx_rx_queue_index(rx_queue));
	MCDI_POPULATE_DWORD_2(inbuf, INIT_RXQ_IN_FLAGS,
			      INIT_RXQ_IN_FLAG_PREFIX, 1,
			      INIT_RXQ_IN_FLAG_TIMESTAMP, 1);
	MCDI_SET_DWORD(inbuf, INIT_RXQ_IN_OWNER_ID, 0);
	MCDI_SET_DWORD(inbuf, INIT_RXQ_IN_PORT_ID, nic_data->vport_id);

	dma_addr = rx_queue->rxd.buf.dma_addr;

	netif_dbg(efx, hw, efx->net_dev, "pushing RXQ %d. %zu entries (%llx)\n",
		  efx_rx_queue_index(rx_queue), entries, (u64)dma_addr);

	for (i = 0; i < entries; ++i) {
		MCDI_SET_ARRAY_QWORD(inbuf, INIT_RXQ_IN_DMA_ADDR, i, dma_addr);
		dma_addr += EFX_BUF_SIZE;
	}

	inlen = MC_CMD_INIT_RXQ_IN_LEN(entries);

	rc = efx_mcdi_rpc(efx, MC_CMD_INIT_RXQ, inbuf, inlen,
			  NULL, 0, NULL);
	if (rc)
		netdev_WARN(efx->net_dev, "failed to initialise RXQ %d\n",
			    efx_rx_queue_index(rx_queue));
}
