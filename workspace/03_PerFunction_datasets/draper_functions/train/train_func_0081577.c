mtip_free_cmd(void *data, struct request *rq,
			  unsigned int hctx_idx, unsigned int request_idx)
{
	struct driver_data *dd = data;
	struct mtip_cmd *cmd = blk_mq_rq_to_pdu(rq);

	if (!cmd->command)
		return;

	dmam_free_coherent(&dd->pdev->dev, CMD_DMA_ALLOC_SZ,
				cmd->command, cmd->command_dma);
}
