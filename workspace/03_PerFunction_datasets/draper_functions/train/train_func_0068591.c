snd_hda_jack_detect_state(struct hda_codec *codec, hda_nid_t nid)
{
	struct hda_jack_tbl *jack = snd_hda_jack_tbl_get(codec, nid);
	if (jack && jack->phantom_jack)
		return HDA_JACK_PHANTOM;
	else if (snd_hda_pin_sense(codec, nid) & AC_PINSENSE_PRESENCE)
		return HDA_JACK_PRESENT;
	else
		return HDA_JACK_NOT_PRESENT;
}
