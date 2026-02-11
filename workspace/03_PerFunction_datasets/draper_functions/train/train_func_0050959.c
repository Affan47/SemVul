pcmidi_snd_terminate(struct pcmidi_snd *pm)
{
	if (pm->card) {
		stop_sustain_timers(pm);

		device_remove_file(&pm->pk->hdev->dev,
			sysfs_device_attr_channel);
		device_remove_file(&pm->pk->hdev->dev,
			sysfs_device_attr_sustain);
		device_remove_file(&pm->pk->hdev->dev,
			sysfs_device_attr_octave);

		snd_card_disconnect(pm->card);
		snd_card_free_when_closed(pm->card);
	}

	return 0;
}
