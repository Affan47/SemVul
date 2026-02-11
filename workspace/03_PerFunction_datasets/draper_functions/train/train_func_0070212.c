mute_ac97_ctl(struct oxygen *chip, unsigned int control)
{
	unsigned int priv_idx;
	u16 value;

	if (!chip->controls[control])
		return;
	priv_idx = chip->controls[control]->private_value & 0xff;
	value = oxygen_read_ac97(chip, 0, priv_idx);
	if (!(value & 0x8000)) {
		oxygen_write_ac97(chip, 0, priv_idx, value | 0x8000);
		if (chip->model.ac97_switch)
			chip->model.ac97_switch(chip, priv_idx, 0x8000);
		snd_ctl_notify(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &chip->controls[control]->id);
	}
}
