snd_info_minor_register(void)
{
	struct snd_info_entry *entry;

	memset(snd_sndstat_strings, 0, sizeof(snd_sndstat_strings));
	entry = snd_info_create_module_entry(THIS_MODULE, "sndstat",
					     snd_oss_root);
	if (!entry)
		return -ENOMEM;
	entry->c.text.read = snd_sndstat_proc_read;
	return snd_info_register(entry);
}
