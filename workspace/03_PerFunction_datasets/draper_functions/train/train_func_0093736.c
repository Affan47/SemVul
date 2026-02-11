pcxhr_proc_init(struct snd_pcxhr *chip)
{
	struct snd_info_entry *entry;

	if (! snd_card_proc_new(chip->card, "info", &entry))
		snd_info_set_text_ops(entry, chip, pcxhr_proc_info);
	if (! snd_card_proc_new(chip->card, "sync", &entry))
		snd_info_set_text_ops(entry, chip, pcxhr_proc_sync);

	if (chip->mgr->is_hr_stereo &&
	    !snd_card_proc_new(chip->card, "gpio", &entry)) {
		snd_info_set_text_ops(entry, chip, pcxhr_proc_gpio_read);
		entry->c.text.write = pcxhr_proc_gpo_write;
		entry->mode |= S_IWUSR;
	}
	if (!snd_card_proc_new(chip->card, "ltc", &entry))
		snd_info_set_text_ops(entry, chip, pcxhr_proc_ltc);
}
