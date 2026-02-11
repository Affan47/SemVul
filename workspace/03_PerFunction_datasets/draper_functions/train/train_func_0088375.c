usdhi6_sg_map(struct usdhi6_host *host)
{
	struct mmc_data *data = host->mrq->data;
	struct scatterlist *sg = data->sg_len > 1 ? host->sg : data->sg;
	size_t head = PAGE_SIZE - sg->offset;
	size_t blk_head = head % data->blksz;

	WARN(host->pg.page, "%p not properly unmapped!\n", host->pg.page);
	if (WARN(sg_dma_len(sg) % data->blksz,
		 "SG size %u isn't a multiple of block size %u\n",
		 sg_dma_len(sg), data->blksz))
		return NULL;

	host->pg.page = sg_page(sg);
	host->pg.mapped = kmap(host->pg.page);
	host->offset = sg->offset;


	host->head_len = blk_head;

	if (head < data->blksz)


		usdhi6_blk_bounce(host, sg);
	else
		host->blk_page = host->pg.mapped;

	dev_dbg(mmc_dev(host->mmc), "Mapped %p (%lx) at %p + %u for CMD%u @ 0x%p\n",
		host->pg.page, page_to_pfn(host->pg.page), host->pg.mapped,
		sg->offset, host->mrq->cmd->opcode, host->mrq);

	return host->blk_page + host->offset;
}
