rrpc_submit_io(struct rrpc *rrpc, struct bio *bio,
				struct nvm_rq *rqd, unsigned long flags)
{
	int err;
	struct rrpc_rq *rrq = nvm_rq_to_pdu(rqd);
	uint8_t nr_pages = rrpc_get_pages(bio);
	int bio_size = bio_sectors(bio) << 9;

	if (bio_size < rrpc->dev->sec_size)
		return NVM_IO_ERR;
	else if (bio_size > rrpc->dev->max_rq_size)
		return NVM_IO_ERR;

	err = rrpc_setup_rq(rrpc, bio, rqd, flags, nr_pages);
	if (err)
		return err;

	bio_get(bio);
	rqd->bio = bio;
	rqd->ins = &rrpc->instance;
	rqd->nr_pages = nr_pages;
	rrq->flags = flags;

	err = nvm_submit_io(rrpc->dev, rqd);
	if (err) {
		pr_err("rrpc: I/O submission failed: %d\n", err);
		bio_put(bio);
		if (!(flags & NVM_IOTYPE_GC)) {
			rrpc_unlock_rq(rrpc, rqd);
			if (rqd->nr_pages > 1)
				nvm_dev_dma_free(rrpc->dev,
			rqd->ppa_list, rqd->dma_ppa_list);
		}
		return NVM_IO_ERR;
	}

	return NVM_IO_OK;
}
