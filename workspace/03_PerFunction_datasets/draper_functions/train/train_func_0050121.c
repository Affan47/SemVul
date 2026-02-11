stac_init_power_map(struct hda_codec *codec)
{
	struct sigmatel_spec *spec = codec->spec;
	int i;

	for (i = 0; i < spec->num_pwrs; i++)  {
		hda_nid_t nid = spec->pwr_nids[i];
		unsigned int def_conf = snd_hda_codec_get_pincfg(codec, nid);
		def_conf = get_defcfg_connect(def_conf);
		if (def_conf == AC_JACK_PORT_COMPLEX &&
		    spec->vref_mute_led_nid != nid &&
		    is_jack_detectable(codec, nid)) {
			snd_hda_jack_detect_enable_callback(codec, nid,
							    jack_update_power);
		} else {
			if (def_conf == AC_JACK_PORT_NONE)
				stac_toggle_power_map(codec, nid, false, false);
			else
				stac_toggle_power_map(codec, nid, true, false);
		}
	}
}
