cx24120_set_voltage(struct dvb_frontend *fe,
			       enum fe_sec_voltage voltage)
{
	struct cx24120_state *state = fe->demodulator_priv;
	struct cx24120_cmd cmd;

	dev_dbg(&state->i2c->dev, "(%d)\n", voltage);

	cmd.id = CMD_SETVOLTAGE;
	cmd.len = 2;
	cmd.arg[0] = 0x00;
	cmd.arg[1] = (voltage == SEC_VOLTAGE_18) ? 0x01 : 0x00;

	return cx24120_message_send(state, &cmd);
}
