stac_capture_pcm_hook(struct hda_pcm_stream *hinfo,
				  struct hda_codec *codec,
				  struct snd_pcm_substream *substream,
				  int action)
{
	struct sigmatel_spec *spec = codec->spec;
	int i, idx = 0;

	if (!spec->powerdown_adcs)
		return;

	for (i = 0; i < spec->gen.num_all_adcs; i++) {
		if (spec->gen.all_adcs[i] == hinfo->nid) {
			idx = i;
			break;
		}
	}

	switch (action) {
	case HDA_GEN_PCM_ACT_OPEN:
		msleep(40);
		snd_hda_codec_write(codec, hinfo->nid, 0,
				    AC_VERB_SET_POWER_STATE, AC_PWRST_D0);
		spec->active_adcs |= (1 << idx);
		break;
	case HDA_GEN_PCM_ACT_CLOSE:
		snd_hda_codec_write(codec, hinfo->nid, 0,
				    AC_VERB_SET_POWER_STATE, AC_PWRST_D3);
		spec->active_adcs &= ~(1 << idx);
		break;
	}
}
