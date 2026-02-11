tda18271_setup_configuration(struct dvb_frontend *fe,
					struct tda18271_config *cfg)
{
	struct tda18271_priv *priv = fe->tuner_priv;

	priv->gate = (cfg) ? cfg->gate : TDA18271_GATE_AUTO;
	priv->role = (cfg) ? cfg->role : TDA18271_MASTER;
	priv->config = (cfg) ? cfg->config : 0;
	priv->small_i2c = (cfg) ?
		cfg->small_i2c : TDA18271_39_BYTE_CHUNK_INIT;
	priv->output_opt = (cfg) ?
		cfg->output_opt : TDA18271_OUTPUT_LT_XT_ON;

	return 0;
}
