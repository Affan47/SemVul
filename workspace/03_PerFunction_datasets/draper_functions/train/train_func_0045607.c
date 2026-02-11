alc282_init(struct hda_codec *codec)
{
	struct alc_spec *spec = codec->spec;
	hda_nid_t hp_pin = spec->gen.autocfg.hp_pins[0];
	bool hp_pin_sense;
	int coef78;

	alc282_restore_default_value(codec);

	if (!hp_pin)
		return;
	hp_pin_sense = snd_hda_jack_detect(codec, hp_pin);
	coef78 = alc_read_coef_idx(codec, 0x78);


	alc_write_coef_idx(codec, 0x78, 0x9004);

	if (hp_pin_sense)
		msleep(2);

	snd_hda_codec_write(codec, hp_pin, 0,
			    AC_VERB_SET_AMP_GAIN_MUTE, AMP_OUT_MUTE);

	if (hp_pin_sense)
		msleep(85);

	snd_hda_codec_write(codec, hp_pin, 0,
			    AC_VERB_SET_PIN_WIDGET_CONTROL, PIN_OUT);

	if (hp_pin_sense)
		msleep(100);


	alc_write_coef_idx(codec, 0x78, coef78);
}
