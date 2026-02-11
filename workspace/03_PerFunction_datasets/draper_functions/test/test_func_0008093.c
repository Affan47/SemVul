snd_m3_mixer(struct snd_m3 *chip)
{
	struct snd_ac97_bus *pbus;
	struct snd_ac97_template ac97;
#ifndef CONFIG_SND_MAESTRO3_INPUT
	struct snd_ctl_elem_id elem_id;
#endif
	int err;
	static struct snd_ac97_bus_ops ops = {
		.write = snd_m3_ac97_write,
		.read = snd_m3_ac97_read,
	};

	if ((err = snd_ac97_bus(chip->card, 0, &ops, NULL, &pbus)) < 0)
		return err;

	memset(&ac97, 0, sizeof(ac97));
	ac97.private_data = chip;
	if ((err = snd_ac97_mixer(pbus, &ac97, &chip->ac97)) < 0)
		return err;


	snd_ac97_write(chip->ac97, AC97_PCM, 0x8000 | (15 << 8) | 15);
	schedule_timeout_uninterruptible(msecs_to_jiffies(100));
	snd_ac97_write(chip->ac97, AC97_PCM, 0);

#ifndef CONFIG_SND_MAESTRO3_INPUT
	memset(&elem_id, 0, sizeof(elem_id));
	elem_id.iface = SNDRV_CTL_ELEM_IFACE_MIXER;
	strcpy(elem_id.name, "Master Playback Switch");
	chip->master_switch = snd_ctl_find_id(chip->card, &elem_id);
	memset(&elem_id, 0, sizeof(elem_id));
	elem_id.iface = SNDRV_CTL_ELEM_IFACE_MIXER;
	strcpy(elem_id.name, "Master Playback Volume");
	chip->master_volume = snd_ctl_find_id(chip->card, &elem_id);
#endif

	return 0;
}
