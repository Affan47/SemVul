snd_ak4114_proc_init(struct ak4114 *ak4114)
{
	struct snd_info_entry *entry;
	if (!snd_card_proc_new(ak4114->card, "ak4114", &entry))
		snd_info_set_text_ops(entry, ak4114, snd_ak4114_proc_regs_read);
}
