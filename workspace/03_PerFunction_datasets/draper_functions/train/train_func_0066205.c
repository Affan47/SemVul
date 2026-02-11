alc233_fixup_lenovo_line2_mic_hotkey(struct hda_codec *codec,
					     const struct hda_fixup *fix, int action)
{


	static const struct hda_verb gpio_init[] = {
		{ 0x01, AC_VERB_SET_GPIO_MASK, 0x04 },
		{ 0x01, AC_VERB_SET_GPIO_DIRECTION, 0x04 },
		{}
	};

	struct alc_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		if (alc_register_micmute_input_device(codec) != 0)
			return;

		snd_hda_add_verbs(codec, gpio_init);
		snd_hda_jack_detect_enable_callback(codec, 0x1b,
						    gpio2_mic_hotkey_event);

		spec->gen.cap_sync_hook = alc_fixup_gpio_mic_mute_hook;
		spec->gpio_led = 0;
		spec->mute_led_polarity = 0;
		spec->gpio_mic_led_mask = 0x04;
		return;
	}

	if (!spec->kb_dev)
		return;

	switch (action) {
	case HDA_FIXUP_ACT_PROBE:
		spec->init_amp = ALC_INIT_DEFAULT;
		break;
	case HDA_FIXUP_ACT_FREE:
		input_unregister_device(spec->kb_dev);
		spec->kb_dev = NULL;
	}
}
