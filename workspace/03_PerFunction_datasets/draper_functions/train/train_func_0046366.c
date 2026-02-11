simple_playback_pcm_open(struct hda_pcm_stream *hinfo,
				    struct hda_codec *codec,
				    struct snd_pcm_substream *substream)
{
	struct hdmi_spec *spec = codec->spec;
	struct snd_pcm_hw_constraint_list *hw_constraints_channels = NULL;

	switch (codec->preset->vendor_id) {
	case 0x10de0002:
	case 0x10de0003:
	case 0x10de0005:
	case 0x10de0006:
		hw_constraints_channels = &hw_constraints_2_8_channels;
		break;
	case 0x10de0007:
		hw_constraints_channels = &hw_constraints_2_6_8_channels;
		break;
	default:
		break;
	}

	if (hw_constraints_channels != NULL) {
		snd_pcm_hw_constraint_list(substream->runtime, 0,
				SNDRV_PCM_HW_PARAM_CHANNELS,
				hw_constraints_channels);
	} else {
		snd_pcm_hw_constraint_step(substream->runtime, 0,
					   SNDRV_PCM_HW_PARAM_CHANNELS, 2);
	}

	return snd_hda_multi_out_dig_open(codec, &spec->multiout);
}
