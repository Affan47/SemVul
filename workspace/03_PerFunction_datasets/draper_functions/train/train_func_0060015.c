rcar_dmac_desc_get(struct rcar_dmac_chan *chan)
{
	struct rcar_dmac_desc *desc;
	unsigned long flags;
	int ret;


	rcar_dmac_desc_recycle_acked(chan);

	spin_lock_irqsave(&chan->lock, flags);

	while (list_empty(&chan->desc.free)) {


		spin_unlock_irqrestore(&chan->lock, flags);
		ret = rcar_dmac_desc_alloc(chan, GFP_NOWAIT);
		if (ret < 0)
			return NULL;
		spin_lock_irqsave(&chan->lock, flags);
	}

	desc = list_first_entry(&chan->desc.free, struct rcar_dmac_desc, node);
	list_del(&desc->node);

	spin_unlock_irqrestore(&chan->lock, flags);

	return desc;
}
