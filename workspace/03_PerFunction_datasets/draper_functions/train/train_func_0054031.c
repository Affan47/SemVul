via_suspend(struct hda_codec *codec)
{
	struct via_spec *spec = codec->spec;
	vt1708_stop_hp_work(codec);


	if (spec->codec_type == VT1802)
		snd_hda_shutup_pins(codec);

	return 0;
}
