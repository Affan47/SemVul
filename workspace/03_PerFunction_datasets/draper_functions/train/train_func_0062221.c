set_pin_target(struct hda_codec *codec, hda_nid_t pin,
			   unsigned int val, bool do_write)
{
	if (!pin)
		return;
	val = snd_hda_correct_pin_ctl(codec, pin, val);
	snd_hda_codec_set_pin_target(codec, pin, val);
	if (do_write)
		update_pin_ctl(codec, pin, val);
}
