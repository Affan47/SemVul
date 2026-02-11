__td_start_dma(struct timb_dma_chan *td_chan)
{
	struct timb_dma_desc *td_desc;

	if (td_chan->ongoing) {
		dev_err(chan2dev(&td_chan->chan),
			"Transfer already ongoing\n");
		return;
	}

	td_desc = list_entry(td_chan->active_list.next, struct timb_dma_desc,
		desc_node);

	dev_dbg(chan2dev(&td_chan->chan),
		"td_chan: %p, chan: %d, membase: %p\n",
		td_chan, td_chan->chan.chan_id, td_chan->membase);

	if (td_chan->direction == DMA_DEV_TO_MEM) {


		iowrite32(0, td_chan->membase + TIMBDMA_OFFS_RX_DHAR);
		iowrite32(td_desc->txd.phys, td_chan->membase +
			TIMBDMA_OFFS_RX_DLAR);

		iowrite32(td_chan->bytes_per_line, td_chan->membase +
			TIMBDMA_OFFS_RX_BPRR);

		iowrite32(TIMBDMA_RX_EN, td_chan->membase + TIMBDMA_OFFS_RX_ER);
	} else {

		iowrite32(0, td_chan->membase + TIMBDMA_OFFS_TX_DHAR);
		iowrite32(td_desc->txd.phys, td_chan->membase +
			TIMBDMA_OFFS_TX_DLAR);
	}

	td_chan->ongoing = true;

	if (td_desc->interrupt)
		__td_enable_chan_irq(td_chan);
}
