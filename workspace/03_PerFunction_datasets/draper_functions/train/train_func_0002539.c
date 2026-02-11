dst_ci_command(struct dst_state* state, u8 * data, u8 *ca_string, u8 len, int read)
{
	u8 reply;

	mutex_lock(&state->dst_mutex);
	dst_comm_init(state);
	msleep(65);

	if (write_dst(state, data, len)) {
		dprintk(verbose, DST_CA_INFO, 1, " Write not successful, trying to recover");
		dst_error_recovery(state);
		goto error;
	}
	if ((dst_pio_disable(state)) < 0) {
		dprintk(verbose, DST_CA_ERROR, 1, " DST PIO disable failed.");
		goto error;
	}
	if (read_dst(state, &reply, GET_ACK) < 0) {
		dprintk(verbose, DST_CA_INFO, 1, " Read not successful, trying to recover");
		dst_error_recovery(state);
		goto error;
	}
	if (read) {
		if (! dst_wait_dst_ready(state, LONG_DELAY)) {
			dprintk(verbose, DST_CA_NOTICE, 1, " 8820 not ready");
			goto error;
		}
		if (read_dst(state, ca_string, 128) < 0) {
			dprintk(verbose, DST_CA_INFO, 1, " Read not successful, trying to recover");
			dst_error_recovery(state);
			goto error;
		}
	}
	mutex_unlock(&state->dst_mutex);
	return 0;

error:
	mutex_unlock(&state->dst_mutex);
	return -EIO;
}
