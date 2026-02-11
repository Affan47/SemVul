mtip_hw_submit_io(struct driver_data *dd, struct request *rq,
			      struct mtip_cmd *command, int nents,
			      struct blk_mq_hw_ctx *hctx)
{
	struct host_to_dev_fis	*fis;
	struct mtip_port *port = dd->port;
	int dma_dir = rq_data_dir(rq) == READ ? DMA_FROM_DEVICE : DMA_TO_DEVICE;
	u64 start = blk_rq_pos(rq);
	unsigned int nsect = blk_rq_sectors(rq);


	nents = dma_map_sg(&dd->pdev->dev, command->sg, nents, dma_dir);

	prefetch(&port->flags);

	command->scatter_ents = nents;


	command->retries = MTIP_MAX_RETRIES;


	fis = command->command;
	fis->type        = 0x27;
	fis->opts        = 1 << 7;
	if (dma_dir == DMA_FROM_DEVICE)
		fis->command = ATA_CMD_FPDMA_READ;
	else
		fis->command = ATA_CMD_FPDMA_WRITE;
	fis->lba_low     = start & 0xFF;
	fis->lba_mid     = (start >> 8) & 0xFF;
	fis->lba_hi      = (start >> 16) & 0xFF;
	fis->lba_low_ex  = (start >> 24) & 0xFF;
	fis->lba_mid_ex  = (start >> 32) & 0xFF;
	fis->lba_hi_ex   = (start >> 40) & 0xFF;
	fis->device	 = 1 << 6;
	fis->features    = nsect & 0xFF;
	fis->features_ex = (nsect >> 8) & 0xFF;
	fis->sect_count  = ((rq->tag << 3) | (rq->tag >> 5));
	fis->sect_cnt_ex = 0;
	fis->control     = 0;
	fis->res2        = 0;
	fis->res3        = 0;
	fill_command_sg(dd, command, nents);

	if (unlikely(command->unaligned))
		fis->device |= 1 << 7;


	command->command_header->opts =
			__force_bit2int cpu_to_le32(
				(nents << 16) | 5 | AHCI_CMD_PREFETCH);
	command->command_header->byte_count = 0;


	command->comp_data = dd;
	command->comp_func = mtip_async_complete;
	command->direction = dma_dir;


	if (unlikely(port->flags & MTIP_PF_PAUSE_IO)) {
		set_bit(rq->tag, port->cmds_to_issue);
		set_bit(MTIP_PF_ISSUE_CMDS_BIT, &port->flags);
		return;
	}


	mtip_issue_ncq_command(port, rq->tag);
}
