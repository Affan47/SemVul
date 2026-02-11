snd_vt1724_resume(struct device *dev)
{
	struct snd_card *card = dev_get_drvdata(dev);
	struct snd_ice1712 *ice = card->private_data;

	if (!ice->pm_suspend_enabled)
		return 0;

	snd_vt1724_chip_reset(ice);

	if (snd_vt1724_chip_init(ice) < 0) {
		snd_card_disconnect(card);
		return -EIO;
	}

	if (ice->pm_resume)
		ice->pm_resume(ice);

	if (ice->pm_saved_is_spdif_master) {

		ice->set_spdif_clock(ice, 0);
	} else {

		int rate;
		if (ice->cur_rate)
			rate = ice->cur_rate;
		else
			rate = ice->pro_rate_default;
		snd_vt1724_set_pro_rate(ice, rate, 1);
	}

	update_spdif_bits(ice, ice->pm_saved_spdif_ctrl);

	outb(ice->pm_saved_spdif_cfg, ICEREG1724(ice, SPDIF_CFG));
	outl(ice->pm_saved_route, ICEMT1724(ice, ROUTE_PLAYBACK));

	snd_ac97_resume(ice->ac97);

	snd_power_change_state(card, SNDRV_CTL_POWER_D0);
	return 0;
}
