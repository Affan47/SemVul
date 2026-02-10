stac9205_fixup_ref(struct hda_codec *codec,
			       const struct hda_fixup *fix, int action)
{
	struct sigmatel_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		snd_hda_apply_pincfgs(codec, ref9205_pin_configs);

		spec->eapd_mask = spec->gpio_mask = spec->gpio_dir = 0;
	}
}
