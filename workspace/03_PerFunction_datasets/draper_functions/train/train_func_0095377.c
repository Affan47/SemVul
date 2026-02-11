tsi721_advance_work(struct tsi721_bdma_chan *bdma_chan)
{
	struct tsi721_tx_desc *desc;
	int err;

	dev_dbg(bdma_chan->dchan.device->dev, "%s: Enter\n", __func__);


	if (!list_empty(&bdma_chan->queue))
		list_splice_init(&bdma_chan->queue, &bdma_chan->active_list);


	if (!list_empty(&bdma_chan->active_list)) {
		desc = tsi721_dma_first_active(bdma_chan);
		err = tsi721_submit_sg(desc);
		if (!err)
			tsi721_start_dma(bdma_chan);
		else {
			tsi721_dma_tx_err(bdma_chan, desc);
			dev_dbg(bdma_chan->dchan.device->dev,
				"ERR: tsi721_submit_sg failed with err=%d\n",
				err);
		}
	}

	dev_dbg(bdma_chan->dchan.device->dev, "%s: Exit\n", __func__);
}
