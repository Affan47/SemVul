create_analog_mixer(struct lola *chip, int dir, char *name)
{
	if (!chip->pin[dir].num_pins)
		return 0;

	if (chip->pin[dir].num_pins != chip->pin[dir].num_analog_pins)
		return 0;
	lola_analog_mixer.name = name;
	lola_analog_mixer.private_value = dir;
	return snd_ctl_add(chip->card,
			   snd_ctl_new1(&lola_analog_mixer, chip));
}
