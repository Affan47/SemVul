register_vga_switcheroo(struct azx *chip)
{
	struct hda_intel *hda = container_of(chip, struct hda_intel, chip);
	int err;

	if (!hda->use_vga_switcheroo)
		return 0;


	err = vga_switcheroo_register_audio_client(chip->pci, &azx_vs_ops,
						   VGA_SWITCHEROO_DIS);
	if (err < 0)
		return err;
	hda->vga_switcheroo_registered = 1;


	vga_switcheroo_init_domain_pm_optimus_hdmi_audio(chip->card->dev,
							 &hda->hdmi_pm_domain);
	return 0;
}
