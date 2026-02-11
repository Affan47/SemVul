orinoco_tmd_cor_reset(struct orinoco_private *priv)
{
	struct hermes *hw = &priv->hw;
	struct orinoco_pci_card *card = priv->card;
	unsigned long timeout;
	u16 reg;

	iowrite8(COR_VALUE | COR_RESET, card->bridge_io);
	mdelay(1);

	iowrite8(COR_VALUE, card->bridge_io);
	mdelay(1);


	timeout = jiffies + msecs_to_jiffies(TMD_RESET_TIME);
	reg = hermes_read_regn(hw, CMD);
	while (time_before(jiffies, timeout) && (reg & HERMES_CMD_BUSY)) {
		mdelay(1);
		reg = hermes_read_regn(hw, CMD);
	}


	if (reg & HERMES_CMD_BUSY) {
		printk(KERN_ERR PFX "Busy timeout\n");
		return -ETIMEDOUT;
	}

	return 0;
}
