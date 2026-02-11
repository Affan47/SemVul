alc_update_gpio_led(struct hda_codec *codec, unsigned int mask,
				bool enabled)
{
	struct alc_spec *spec = codec->spec;
	unsigned int oldval = spec->gpio_led;

	if (spec->mute_led_polarity)
		enabled = !enabled;

	if (enabled)
		spec->gpio_led &= ~mask;
	else
		spec->gpio_led |= mask;
	if (spec->gpio_led != oldval)
		snd_hda_codec_write(codec, 0x01, 0, AC_VERB_SET_GPIO_DATA,
				    spec->gpio_led);
}
