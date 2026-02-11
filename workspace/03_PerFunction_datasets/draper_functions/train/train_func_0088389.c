register_device(void)
{
	int rc;

	mutex_lock(&register_mutex);
	if ((rc = snd_register_oss_device(SNDRV_OSS_DEVICE_TYPE_SEQUENCER,
					  NULL, 0,
					  &seq_oss_f_ops, NULL)) < 0) {
		pr_err("ALSA: seq_oss: can't register device seq\n");
		mutex_unlock(&register_mutex);
		return rc;
	}
	if ((rc = snd_register_oss_device(SNDRV_OSS_DEVICE_TYPE_MUSIC,
					  NULL, 0,
					  &seq_oss_f_ops, NULL)) < 0) {
		pr_err("ALSA: seq_oss: can't register device music\n");
		snd_unregister_oss_device(SNDRV_OSS_DEVICE_TYPE_SEQUENCER, NULL, 0);
		mutex_unlock(&register_mutex);
		return rc;
	}
	mutex_unlock(&register_mutex);
	return 0;
}
