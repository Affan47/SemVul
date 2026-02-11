cleanup_dig_out_stream(struct hda_codec *codec, hda_nid_t nid)
{
	snd_hda_codec_cleanup_stream(codec, nid);
	if (codec->slave_dig_outs) {
		const hda_nid_t *d;
		for (d = codec->slave_dig_outs; *d; d++)
			snd_hda_codec_cleanup_stream(codec, *d);
	}
}
