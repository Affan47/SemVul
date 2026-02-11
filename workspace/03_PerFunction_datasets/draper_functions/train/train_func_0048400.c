dst_set_diseqc(struct dvb_frontend *fe, struct dvb_diseqc_master_cmd *cmd)
{
	struct dst_state *state = fe->demodulator_priv;
	u8 paket[8] = { 0x00, 0x08, 0x04, 0xe0, 0x10, 0x38, 0xf0, 0xec };

	if (state->dst_type != DST_TYPE_IS_SAT)
		return -EOPNOTSUPP;
	if (cmd->msg_len > 0 && cmd->msg_len < 5)
		memcpy(&paket[3], cmd->msg, cmd->msg_len);
	else if (cmd->msg_len == 5 && state->dst_hw_cap & DST_TYPE_HAS_DISEQC5)
		memcpy(&paket[2], cmd->msg, cmd->msg_len);
	else
		return -EINVAL;
	paket[7] = dst_check_sum(&paket[0], 7);
	return dst_command(state, paket, 8);
}
