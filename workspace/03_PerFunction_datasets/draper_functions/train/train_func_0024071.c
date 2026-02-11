m88rs2000_get_tune_settings(struct dvb_frontend *fe,
	struct dvb_frontend_tune_settings *tune)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;

	if (c->symbol_rate > 3000000)
		tune->min_delay_ms = 2000;
	else
		tune->min_delay_ms = 3000;

	tune->step_size = c->symbol_rate / 16000;
	tune->max_drift = c->symbol_rate / 2000;

	return 0;
}
