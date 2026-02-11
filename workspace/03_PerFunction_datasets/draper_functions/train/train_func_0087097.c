fe_set_params(struct dvb_frontend *fe,
			  struct analog_parameters *params)
{
	struct dvb_tuner_ops *fe_tuner_ops = &fe->ops.tuner_ops;
	struct tuner *t = fe->analog_demod_priv;

	if (NULL == fe_tuner_ops->set_analog_params) {
		tuner_warn("Tuner frontend module has no way to set freq\n");
		return;
	}
	fe_tuner_ops->set_analog_params(fe, params);
}
