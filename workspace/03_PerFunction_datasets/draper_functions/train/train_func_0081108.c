b1dma_load_firmware(struct capi_ctr *ctrl, capiloaddata *data)
{
	avmctrl_info *cinfo = (avmctrl_info *)(ctrl->driverdata);
	avmcard *card = cinfo->card;
	int retval;

	b1dma_reset(card);

	if ((retval = b1_load_t4file(card, &data->firmware))) {
		b1dma_reset(card);
		printk(KERN_ERR "%s: failed to load t4file!!\n",
		       card->name);
		return retval;
	}

	if (data->configuration.len > 0 && data->configuration.data) {
		if ((retval = b1_load_config(card, &data->configuration))) {
			b1dma_reset(card);
			printk(KERN_ERR "%s: failed to load config!!\n",
			       card->name);
			return retval;
		}
	}

	if (!b1dma_loaded(card)) {
		b1dma_reset(card);
		printk(KERN_ERR "%s: failed to load t4file.\n", card->name);
		return -EIO;
	}

	card->csr = AVM_FLAG;
	b1dma_writel(card, card->csr, AMCC_INTCSR);
	b1dma_writel(card, EN_A2P_TRANSFERS | EN_P2A_TRANSFERS | A2P_HI_PRIORITY |
		     P2A_HI_PRIORITY | RESET_A2P_FLAGS | RESET_P2A_FLAGS,
		     AMCC_MCSR);
	t1outp(card->port, 0x07, 0x30);
	t1outp(card->port, 0x10, 0xF0);

	card->dma->recvlen = 0;
	b1dma_writel(card, card->dma->recvbuf.dmaaddr, AMCC_RXPTR);
	b1dma_writel(card, 4, AMCC_RXLEN);
	card->csr |= EN_RX_TC_INT;
	b1dma_writel(card, card->csr, AMCC_INTCSR);

	b1dma_send_init(card);

	return 0;
}
