es1968_update_hw_volume(struct work_struct *work)
{
	struct es1968 *chip = container_of(work, struct es1968, hwvol_work);
	int x, val;


	x = inb(chip->io_port + 0x1c) & 0xee;

	outb(0x88, chip->io_port + 0x1c);
	outb(0x88, chip->io_port + 0x1d);
	outb(0x88, chip->io_port + 0x1e);
	outb(0x88, chip->io_port + 0x1f);

	if (chip->in_suspend)
		return;

#ifndef CONFIG_SND_ES1968_INPUT
	if (! chip->master_switch || ! chip->master_volume)
		return;

	val = snd_ac97_read(chip->ac97, AC97_MASTER);
	switch (x) {
	case 0x88:

		val ^= 0x8000;
		break;
	case 0xaa:

		if ((val & 0x7f) > 0)
			val--;
		if ((val & 0x7f00) > 0)
			val -= 0x0100;
		break;
	case 0x66:

		if ((val & 0x7f) < 0x1f)
			val++;
		if ((val & 0x7f00) < 0x1f00)
			val += 0x0100;
		break;
	}
	if (snd_ac97_update(chip->ac97, AC97_MASTER, val))
		snd_ctl_notify(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &chip->master_volume->id);
#else
	if (!chip->input_dev)
		return;

	val = 0;
	switch (x) {
	case 0x88:


		val = KEY_MUTE;
		break;
	case 0xaa:

		val = KEY_VOLUMEUP;
		break;
	case 0x66:

		val = KEY_VOLUMEDOWN;
		break;
	}

	if (val) {
		input_report_key(chip->input_dev, val, 1);
		input_sync(chip->input_dev);
		input_report_key(chip->input_dev, val, 0);
		input_sync(chip->input_dev);
	}
#endif
}
