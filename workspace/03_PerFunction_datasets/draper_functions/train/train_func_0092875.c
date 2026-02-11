snd_hda_multi_out_analog_open(struct hda_codec *codec,
				  struct hda_multi_out *mout,
				  struct snd_pcm_substream *substream,
				  struct hda_pcm_stream *hinfo)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	runtime->hw.channels_max = mout->max_channels;
	if (mout->dig_out_nid) {
		if (!mout->analog_rates) {
			mout->analog_rates = hinfo->rates;
			mout->analog_formats = hinfo->formats;
			mout->analog_maxbps = hinfo->maxbps;
		} else {
			runtime->hw.rates = mout->analog_rates;
			runtime->hw.formats = mout->analog_formats;
			hinfo->maxbps = mout->analog_maxbps;
		}
		if (!mout->spdif_rates) {
			snd_hda_query_supported_pcm(codec, mout->dig_out_nid,
						    &mout->spdif_rates,
						    &mout->spdif_formats,
						    &mout->spdif_maxbps);
		}
		mutex_lock(&codec->spdif_mutex);
		if (mout->share_spdif) {
			if ((runtime->hw.rates & mout->spdif_rates) &&
			    (runtime->hw.formats & mout->spdif_formats)) {
				runtime->hw.rates &= mout->spdif_rates;
				runtime->hw.formats &= mout->spdif_formats;
				if (mout->spdif_maxbps < hinfo->maxbps)
					hinfo->maxbps = mout->spdif_maxbps;
			} else {
				mout->share_spdif = 0;

			}
		}
		mutex_unlock(&codec->spdif_mutex);
	}
	return snd_pcm_hw_constraint_step(substream->runtime, 0,
					  SNDRV_PCM_HW_PARAM_CHANNELS, 2);
}
