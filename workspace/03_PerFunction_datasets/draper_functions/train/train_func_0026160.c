snd_emux_delete_virmidi(struct snd_emux *emu)
{
	int i;

	if (emu->vmidi == NULL)
		return 0;

	for (i = 0; i < emu->midi_ports; i++) {
		if (emu->vmidi[i])
			snd_device_free(emu->card, emu->vmidi[i]);
	}
	kfree(emu->vmidi);
	emu->vmidi = NULL;
	return 0;
}
