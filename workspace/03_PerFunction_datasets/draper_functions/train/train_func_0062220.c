cs46xx_dsp_disable_spdif_in (struct snd_cs46xx *chip)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;

	if (snd_BUG_ON(!ins->asynch_rx_scb))
		return -EINVAL;
	if (snd_BUG_ON(!ins->spdif_in_src))
		return -EINVAL;

	mutex_lock(&chip->spos_mutex);


	cs46xx_dsp_remove_scb (chip,ins->asynch_rx_scb);
	ins->asynch_rx_scb = NULL;

	cs46xx_src_unlink(chip,ins->spdif_in_src);


	ins->spdif_status_in = 0;
	mutex_unlock(&chip->spos_mutex);


	chip->active_ctrl(chip, -1);
	chip->amplifier_ctrl(chip, -1);

	return 0;
}
