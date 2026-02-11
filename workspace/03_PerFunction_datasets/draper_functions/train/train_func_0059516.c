pch_dma_save_regs(struct pch_dma *pd)
{
	struct pch_dma_chan *pd_chan;
	struct dma_chan *chan, *_c;
	int i = 0;

	pd->regs.dma_ctl0 = dma_readl(pd, CTL0);
	pd->regs.dma_ctl1 = dma_readl(pd, CTL1);
	pd->regs.dma_ctl2 = dma_readl(pd, CTL2);
	pd->regs.dma_ctl3 = dma_readl(pd, CTL3);

	list_for_each_entry_safe(chan, _c, &pd->dma.channels, device_node) {
		pd_chan = to_pd_chan(chan);

		pd->ch_regs[i].dev_addr = channel_readl(pd_chan, DEV_ADDR);
		pd->ch_regs[i].mem_addr = channel_readl(pd_chan, MEM_ADDR);
		pd->ch_regs[i].size = channel_readl(pd_chan, SIZE);
		pd->ch_regs[i].next = channel_readl(pd_chan, NEXT);

		i++;
	}
}
