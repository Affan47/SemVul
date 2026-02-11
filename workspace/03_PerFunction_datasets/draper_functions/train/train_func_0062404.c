lg216x_get_tune_settings(struct dvb_frontend *fe,
				    struct dvb_frontend_tune_settings
				    *fe_tune_settings)
{
	fe_tune_settings->min_delay_ms = 500;
	lg_dbg("\n");
	return 0;
}
