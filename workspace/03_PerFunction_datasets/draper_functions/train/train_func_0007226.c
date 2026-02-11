snd_ymfpci_hw_start(struct snd_ymfpci *chip)
{
	unsigned long flags;

	spin_lock_irqsave(&chip->reg_lock, flags);
	if (chip->start_count++ > 0)
		goto __end;
	snd_ymfpci_writel(chip, YDSXGR_MODE,
			  snd_ymfpci_readl(chip, YDSXGR_MODE) | 3);
	chip->active_bank = snd_ymfpci_readl(chip, YDSXGR_CTRLSELECT) & 1;
      __end:
      	spin_unlock_irqrestore(&chip->reg_lock, flags);
}
