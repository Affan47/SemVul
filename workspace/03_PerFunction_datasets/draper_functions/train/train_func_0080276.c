snd_cmipci_playback_spdif_prepare(struct snd_pcm_substream *substream)
{
	struct cmipci *cm = snd_pcm_substream_chip(substream);
	int err, do_ac3;

	if (cm->can_ac3_hw)
		do_ac3 = cm->dig_pcm_status & IEC958_AES0_NONAUDIO;
	else
		do_ac3 = 1;
	if ((err = setup_spdif_playback(cm, substream, 1, do_ac3)) < 0)
		return err;
	return snd_cmipci_pcm_prepare(cm, &cm->channel[CM_CH_PLAY], substream);
}
