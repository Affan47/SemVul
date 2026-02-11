sync_all_pin_power_ctls(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	struct auto_pin_cfg *cfg = &spec->autocfg;
	int i;

	if (!codec->power_save_node)
		return;
	sync_pin_power_ctls(codec, cfg->line_outs, cfg->line_out_pins);
	if (cfg->line_out_type != AUTO_PIN_HP_OUT)
		sync_pin_power_ctls(codec, cfg->hp_outs, cfg->hp_pins);
	if (cfg->line_out_type != AUTO_PIN_SPEAKER_OUT)
		sync_pin_power_ctls(codec, cfg->speaker_outs, cfg->speaker_pins);
	for (i = 0; i < cfg->num_inputs; i++)
		sync_pin_power_ctls(codec, 1, &cfg->inputs[i].pin);
}
