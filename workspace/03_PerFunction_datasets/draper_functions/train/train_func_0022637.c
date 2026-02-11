init_vga_switcheroo(struct azx *chip)
{
	struct hda_intel *hda = container_of(chip, struct hda_intel, chip);
	struct pci_dev *p = get_bound_vga(chip->pci);
	if (p) {
		dev_info(chip->card->dev,
			 "Handle vga_switcheroo audio client\n");
		hda->use_vga_switcheroo = 1;
		pci_dev_put(p);
	}
}
