rrpc_write_ppalist_rq(struct rrpc *rrpc, struct bio *bio,
			struct nvm_rq *rqd, unsigned long flags, int npages)
{
	struct rrpc_inflight_rq *r = rrpc_get_inflight_rq(rqd);
	struct rrpc_addr *p;
	sector_t laddr = rrpc_get_laddr(bio);
	int is_gc = flags & NVM_IOTYPE_GC;
	int i;

	if (!is_gc && rrpc_lock_rq(rrpc, bio, rqd)) {
		nvm_dev_dma_free(rrpc->dev, rqd->ppa_list, rqd->dma_ppa_list);
		return NVM_IO_REQUEUE;
	}

	for (i = 0; i < npages; i++) {

		p = rrpc_map_page(rrpc, laddr + i, is_gc);
		if (!p) {
			BUG_ON(is_gc);
			rrpc_unlock_laddr(rrpc, r);
			nvm_dev_dma_free(rrpc->dev, rqd->ppa_list,
							rqd->dma_ppa_list);
			rrpc_gc_kick(rrpc);
			return NVM_IO_REQUEUE;
		}

		rqd->ppa_list[i] = rrpc_ppa_to_gaddr(rrpc->dev,
								p->addr);
	}

	rqd->opcode = NVM_OP_HBWRITE;

	return NVM_IO_OK;
}
