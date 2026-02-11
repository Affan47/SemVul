hsw_volume_put(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_platform *platform = snd_soc_kcontrol_platform(kcontrol);
	struct hsw_priv_data *pdata = snd_soc_platform_get_drvdata(platform);
	struct sst_hsw *hsw = pdata->hsw;
	u32 volume;

	pm_runtime_get_sync(pdata->dev);

	if (ucontrol->value.integer.value[0] ==
		ucontrol->value.integer.value[1]) {

		volume = hsw_mixer_to_ipc(ucontrol->value.integer.value[0]);
		sst_hsw_mixer_set_volume(hsw, 0, SST_HSW_CHANNELS_ALL, volume);

	} else {
		volume = hsw_mixer_to_ipc(ucontrol->value.integer.value[0]);
		sst_hsw_mixer_set_volume(hsw, 0, 0, volume);

		volume = hsw_mixer_to_ipc(ucontrol->value.integer.value[1]);
		sst_hsw_mixer_set_volume(hsw, 0, 1, volume);
	}

	pm_runtime_mark_last_busy(pdata->dev);
	pm_runtime_put_autosuspend(pdata->dev);
	return 0;
}
