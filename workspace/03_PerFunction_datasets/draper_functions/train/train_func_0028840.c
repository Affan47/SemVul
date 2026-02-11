snd_ymfpci_resume(struct device *dev)
{
	struct pci_dev *pci = to_pci_dev(dev);
	struct snd_card *card = dev_get_drvdata(dev);
	struct snd_ymfpci *chip = card->private_data;
	unsigned int i;

	snd_ymfpci_aclink_reset(pci);
	snd_ymfpci_codec_ready(chip, 0);
	snd_ymfpci_download_image(chip);
	udelay(100);

	for (i = 0; i < YDSXGR_NUM_SAVED_REGS; i++)
		snd_ymfpci_writel(chip, saved_regs_index[i], chip->saved_regs[i]);

	snd_ac97_resume(chip->ac97);

	pci_write_config_word(chip->pci, PCIR_DSXG_LEGACY,
			      chip->saved_dsxg_legacy);
	pci_write_config_word(chip->pci, PCIR_DSXG_ELEGACY,
			      chip->saved_dsxg_elegacy);


	if (chip->start_count > 0) {
		spin_lock_irq(&chip->reg_lock);
		snd_ymfpci_writel(chip, YDSXGR_MODE, chip->saved_ydsxgr_mode);
		chip->active_bank = snd_ymfpci_readl(chip, YDSXGR_CTRLSELECT);
		spin_unlock_irq(&chip->reg_lock);
	}
	snd_power_change_state(card, SNDRV_CTL_POWER_D0);
	return 0;
}
