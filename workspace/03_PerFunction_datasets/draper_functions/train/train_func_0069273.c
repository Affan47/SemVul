cx_auto_turn_eapd(struct hda_codec *codec, int num_pins,
			      hda_nid_t *pins, bool on)
{
	int i;
	for (i = 0; i < num_pins; i++) {
		if (snd_hda_query_pin_caps(codec, pins[i]) & AC_PINCAP_EAPD)
			snd_hda_codec_write(codec, pins[i], 0,
					    AC_VERB_SET_EAPD_BTLENABLE,
					    on ? 0x02 : 0);
	}
}
