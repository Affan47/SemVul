va1j5jf8007s_set_ts_id(struct va1j5jf8007s_state *state)
{
	u32 ts_id;
	u8 buf[3];
	struct i2c_msg msg;

	ts_id = state->fe.dtv_property_cache.stream_id;
	if (!ts_id || ts_id == NO_STREAM_ID_FILTER)
		return 0;

	buf[0] = 0x8f;
	buf[1] = ts_id >> 8;
	buf[2] = ts_id;

	msg.addr = state->config->demod_address;
	msg.flags = 0;
	msg.len = sizeof(buf);
	msg.buf = buf;

	if (i2c_transfer(state->adap, &msg, 1) != 1)
		return -EREMOTEIO;

	return 0;
}
