setup_corb_rirb(struct lola *chip)
{
	int err;
	unsigned char tmp;
	unsigned long end_time;

	err = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV,
				  snd_dma_pci_data(chip->pci),
				  PAGE_SIZE, &chip->rb);
	if (err < 0)
		return err;

	chip->corb.addr = chip->rb.addr;
	chip->corb.buf = (u32 *)chip->rb.area;
	chip->rirb.addr = chip->rb.addr + 2048;
	chip->rirb.buf = (u32 *)(chip->rb.area + 2048);


	lola_writeb(chip, BAR0, RIRBCTL, 0);
	lola_writeb(chip, BAR0, CORBCTL, 0);

	end_time = jiffies + msecs_to_jiffies(200);
	do {
		if (!lola_readb(chip, BAR0, RIRBCTL) &&
		    !lola_readb(chip, BAR0, CORBCTL))
			break;
		msleep(1);
	} while (time_before(jiffies, end_time));


	lola_writel(chip, BAR0, CORBLBASE, (u32)chip->corb.addr);
	lola_writel(chip, BAR0, CORBUBASE, upper_32_bits(chip->corb.addr));

	lola_writeb(chip, BAR0, CORBSIZE, 0x02);

	lola_writew(chip, BAR0, CORBWP, 0);

	lola_writew(chip, BAR0, CORBRP, LOLA_RBRWP_CLR);

	lola_writeb(chip, BAR0, CORBCTL, LOLA_RBCTL_DMA_EN);

	tmp = lola_readb(chip, BAR0, CORBSTS) & LOLA_CORB_INT_MASK;
	if (tmp)
		lola_writeb(chip, BAR0, CORBSTS, tmp);
	chip->corb.wp = 0;


	lola_writel(chip, BAR0, RIRBLBASE, (u32)chip->rirb.addr);
	lola_writel(chip, BAR0, RIRBUBASE, upper_32_bits(chip->rirb.addr));

	lola_writeb(chip, BAR0, RIRBSIZE, 0x02);

	lola_writew(chip, BAR0, RIRBWP, LOLA_RBRWP_CLR);

	lola_writew(chip, BAR0, RINTCNT, 1);

	lola_writeb(chip, BAR0, RIRBCTL, LOLA_RBCTL_DMA_EN | LOLA_RBCTL_IRQ_EN);

	tmp =  lola_readb(chip, BAR0, RIRBSTS) & LOLA_RIRB_INT_MASK;
	if (tmp)
		lola_writeb(chip, BAR0, RIRBSTS, tmp);
	chip->rirb.rp = chip->rirb.cmds = 0;

	return 0;
}
