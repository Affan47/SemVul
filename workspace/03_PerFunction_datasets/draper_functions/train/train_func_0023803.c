ch7006_setup_levels(struct drm_encoder *encoder)
{
	struct i2c_client *client = drm_i2c_encoder_get_client(encoder);
	struct ch7006_priv *priv = to_ch7006_priv(encoder);
	uint8_t *regs = priv->state.regs;
	const struct ch7006_tv_norm_info *norm = &ch7006_tv_norms[priv->norm];
	int gain;
	int black_level;


	if (norm->black_level < 339*fixed1/1000) {
		gain = 76;

		regs[CH7006_INPUT_FORMAT] |= CH7006_INPUT_FORMAT_DAC_GAIN;
	} else {
		gain = 71;

		regs[CH7006_INPUT_FORMAT] &= ~CH7006_INPUT_FORMAT_DAC_GAIN;
	}

	black_level = round_fixed(norm->black_level*26625)/gain;


	black_level = interpolate(90, black_level, 208, priv->brightness);

	regs[CH7006_BLACK_LEVEL] = bitf(CH7006_BLACK_LEVEL_0, black_level);

	ch7006_dbg(client, "black level: %d\n", black_level);
}
