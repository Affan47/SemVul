rcar_dmac_isr_channel_thread(int irq, void *dev)
{
	struct rcar_dmac_chan *chan = dev;
	struct rcar_dmac_desc *desc;

	spin_lock_irq(&chan->lock);


	if (chan->desc.running && chan->desc.running->cyclic) {
		dma_async_tx_callback callback;
		void *callback_param;

		desc = chan->desc.running;
		callback = desc->async_tx.callback;
		callback_param = desc->async_tx.callback_param;

		if (callback) {
			spin_unlock_irq(&chan->lock);
			callback(callback_param);
			spin_lock_irq(&chan->lock);
		}
	}


	while (!list_empty(&chan->desc.done)) {
		desc = list_first_entry(&chan->desc.done, struct rcar_dmac_desc,
					node);
		dma_cookie_complete(&desc->async_tx);
		list_del(&desc->node);

		if (desc->async_tx.callback) {
			spin_unlock_irq(&chan->lock);


			desc->async_tx.callback(desc->async_tx.callback_param);
			spin_lock_irq(&chan->lock);
		}

		list_add_tail(&desc->node, &chan->desc.wait);
	}

	spin_unlock_irq(&chan->lock);


	rcar_dmac_desc_recycle_acked(chan);

	return IRQ_HANDLED;
}
