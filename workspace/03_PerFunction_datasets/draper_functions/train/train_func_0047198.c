print_pin_widget(struct snd_info_buffer *buffer,
			     struct lola *chip, int nid, unsigned int ampcap,
			     const char *name)
{
	unsigned int val;

	lola_read_param(chip, nid, LOLA_PAR_AUDIO_WIDGET_CAP, &val);
	snd_iprintf(buffer, "Node 0x%02x %s wcaps 0x%x\n", nid, name, val);
	if (val == 0x00400200)
		return;
	lola_read_param(chip, nid, ampcap, &val);
	snd_iprintf(buffer, "  Amp-Caps: 0x%x\n", val);
	snd_iprintf(buffer, "    mute=%d, step-size=%d, steps=%d, ofs=%d\n",
		    LOLA_AMP_MUTE_CAPABLE(val),
		    LOLA_AMP_STEP_SIZE(val),
		    LOLA_AMP_NUM_STEPS(val),
		    LOLA_AMP_OFFSET(val));
	lola_codec_read(chip, nid, LOLA_VERB_GET_MAX_LEVEL, 0, 0, &val, NULL);
	snd_iprintf(buffer, "  Max-level: 0x%x\n", val);
}
