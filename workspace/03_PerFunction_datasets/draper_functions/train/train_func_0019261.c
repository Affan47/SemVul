snd_hda_codec_set_name(struct hda_codec *codec, const char *name)
{
	int err;

	if (!name)
		return 0;
	err = snd_hdac_device_set_chip_name(&codec->core, name);
	if (err < 0)
		return err;


	if (!*codec->card->mixername ||
	    codec->bus->mixer_assigned >= codec->core.addr) {
		snprintf(codec->card->mixername,
			 sizeof(codec->card->mixername), "%s %s",
			 codec->core.vendor_name, codec->core.chip_name);
		codec->bus->mixer_assigned = codec->core.addr;
	}

	return 0;
}
