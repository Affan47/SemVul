cx24117_release(struct dvb_frontend *fe)
{
	struct cx24117_state *state = fe->demodulator_priv;
	dev_dbg(&state->priv->i2c->dev, "%s demod%d\n",
		__func__, state->demod);
	cx24117_release_priv(state->priv);
	kfree(state);
}
