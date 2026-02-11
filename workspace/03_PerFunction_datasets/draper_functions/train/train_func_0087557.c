snd_pdacf_create(struct snd_card *card)
{
	struct snd_pdacf *chip;

	chip = kzalloc(sizeof(*chip), GFP_KERNEL);
	if (chip == NULL)
		return NULL;
	chip->card = card;
	mutex_init(&chip->reg_lock);
	spin_lock_init(&chip->ak4117_lock);
	card->private_data = chip;

	pdacf_proc_init(chip);
	return chip;
}
