tuner_s_config(struct v4l2_subdev *sd,
			  const struct v4l2_priv_tun_config *cfg)
{
	struct tuner *t = to_tuner(sd);
	struct analog_demod_ops *analog_ops = &t->fe.ops.analog_ops;

	if (t->type != cfg->tuner)
		return 0;

	if (analog_ops->set_config) {
		analog_ops->set_config(&t->fe, cfg->priv);
		return 0;
	}

	tuner_dbg("Tuner frontend module has no way to set config\n");
	return 0;
}
