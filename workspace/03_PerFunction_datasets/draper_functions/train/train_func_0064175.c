es1968_suspend(struct device *dev)
{
	struct snd_card *card = dev_get_drvdata(dev);
	struct es1968 *chip = card->private_data;

	if (! chip->do_pm)
		return 0;

	chip->in_suspend = 1;
	cancel_work_sync(&chip->hwvol_work);
	snd_power_change_state(card, SNDRV_CTL_POWER_D3hot);
	snd_pcm_suspend_all(chip->pcm);
	snd_ac97_suspend(chip->ac97);
	snd_es1968_bob_stop(chip);
	return 0;
}
