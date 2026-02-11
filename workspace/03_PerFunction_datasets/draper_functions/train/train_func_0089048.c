azx_vs_set_state(struct pci_dev *pci,
			     enum vga_switcheroo_state state)
{
	struct snd_card *card = pci_get_drvdata(pci);
	struct azx *chip = card->private_data;
	struct hda_intel *hda = container_of(chip, struct hda_intel, chip);
	bool disabled;

	wait_for_completion(&hda->probe_wait);
	if (hda->init_failed)
		return;

	disabled = (state == VGA_SWITCHEROO_OFF);
	if (chip->disabled == disabled)
		return;

	if (!hda->probe_continued) {
		chip->disabled = disabled;
		if (!disabled) {
			dev_info(chip->card->dev,
				 "Start delayed initialization\n");
			if (azx_probe_continue(chip) < 0) {
				dev_err(chip->card->dev, "initialization error\n");
				hda->init_failed = true;
			}
		}
	} else {
		dev_info(chip->card->dev, "%s via vga_switcheroo\n",
			 disabled ? "Disabling" : "Enabling");
		if (disabled) {
			pm_runtime_put_sync_suspend(card->dev);
			azx_suspend(card->dev);


			pci->current_state = PCI_D3cold;
			chip->disabled = true;
			if (snd_hda_lock_devices(&chip->bus))
				dev_warn(chip->card->dev,
					 "Cannot lock devices!\n");
		} else {
			snd_hda_unlock_devices(&chip->bus);
			pm_runtime_get_noresume(card->dev);
			chip->disabled = false;
			azx_resume(card->dev);
		}
	}
}
