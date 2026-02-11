sst_hsw_mixer_get_volume(struct sst_hsw *hsw, u32 stage_id, u32 channel,
	u32 *volume)
{
	if (channel > 1)
		return -EINVAL;

	sst_dsp_read(hsw->dsp, volume,
		hsw->mixer_info.volume_register_address[channel],
		sizeof(*volume));

	return 0;
}
