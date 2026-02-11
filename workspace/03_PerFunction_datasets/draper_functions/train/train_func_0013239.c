cx24120_diseqc_send_burst(struct dvb_frontend *fe,
				     enum fe_sec_mini_cmd burst)
{
	struct cx24120_state *state = fe->demodulator_priv;
	struct cx24120_cmd cmd;

	dev_dbg(&state->i2c->dev, "\n");


	cmd.id = CMD_DISEQC_BURST;
	cmd.len = 0;
	cmd.arg[0] = 0x00;
	cmd.arg[1] = (burst == SEC_MINI_B) ? 0x01 : 0x00;

	return cx24120_message_send(state, &cmd);
}
