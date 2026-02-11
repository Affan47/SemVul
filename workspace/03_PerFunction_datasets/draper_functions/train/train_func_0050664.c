tsi721_prep_rio_sg(struct dma_chan *dchan,
			struct scatterlist *sgl, unsigned int sg_len,
			enum dma_transfer_direction dir, unsigned long flags,
			void *tinfo)
{
	struct tsi721_bdma_chan *bdma_chan = to_tsi721_chan(dchan);
	struct tsi721_tx_desc *desc, *_d;
	struct rio_dma_ext *rext = tinfo;
	enum dma_rtype rtype;
	struct dma_async_tx_descriptor *txd = NULL;

	if (!sgl || !sg_len) {
		dev_err(dchan->device->dev, "%s: No SG list\n", __func__);
		return NULL;
	}

	dev_dbg(dchan->device->dev, "%s: %s\n", __func__,
		(dir == DMA_DEV_TO_MEM)?"READ":"WRITE");

	if (dir == DMA_DEV_TO_MEM)
		rtype = NREAD;
	else if (dir == DMA_MEM_TO_DEV) {
		switch (rext->wr_type) {
		case RDW_ALL_NWRITE:
			rtype = ALL_NWRITE;
			break;
		case RDW_ALL_NWRITE_R:
			rtype = ALL_NWRITE_R;
			break;
		case RDW_LAST_NWRITE_R:
		default:
			rtype = LAST_NWRITE_R;
			break;
		}
	} else {
		dev_err(dchan->device->dev,
			"%s: Unsupported DMA direction option\n", __func__);
		return NULL;
	}

	spin_lock_bh(&bdma_chan->lock);

	list_for_each_entry_safe(desc, _d, &bdma_chan->free_list, desc_node) {
		if (async_tx_test_ack(&desc->txd)) {
			list_del_init(&desc->desc_node);
			desc->destid = rext->destid;
			desc->rio_addr = rext->rio_addr;
			desc->rio_addr_u = 0;
			desc->rtype = rtype;
			desc->sg_len	= sg_len;
			desc->sg	= sgl;
			txd		= &desc->txd;
			txd->flags	= flags;
			break;
		}
	}

	spin_unlock_bh(&bdma_chan->lock);

	return txd;
}
