ca0132_build_controls(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;
	int i, num_fx;
	int err = 0;


	for (i = 0; i < spec->num_mixers; i++) {
		err = snd_hda_add_new_ctls(codec, spec->mixers[i]);
		if (err < 0)
			return err;
	}


	num_fx = OUT_EFFECTS_COUNT + IN_EFFECTS_COUNT;
	for (i = 0; i < num_fx; i++) {
		err = add_fx_switch(codec, ca0132_effects[i].nid,
				    ca0132_effects[i].name,
				    ca0132_effects[i].direct);
		if (err < 0)
			return err;
	}

	err = add_fx_switch(codec, PLAY_ENHANCEMENT, "PlayEnhancement", 0);
	if (err < 0)
		return err;

	err = add_fx_switch(codec, CRYSTAL_VOICE, "CrystalVoice", 1);
	if (err < 0)
		return err;

	add_voicefx(codec);

#ifdef ENABLE_TUNING_CONTROLS
	add_tuning_ctls(codec);
#endif

	err = snd_hda_jack_add_kctls(codec, &spec->autocfg);
	if (err < 0)
		return err;

	if (spec->dig_out) {
		err = snd_hda_create_spdif_out_ctls(codec, spec->dig_out,
						    spec->dig_out);
		if (err < 0)
			return err;
		err = snd_hda_create_spdif_share_sw(codec, &spec->multiout);
		if (err < 0)
			return err;

	}

	if (spec->dig_in) {
		err = snd_hda_create_spdif_in_ctls(codec, spec->dig_in);
		if (err < 0)
			return err;
	}
	return 0;
}
