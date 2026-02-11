S01T_set(struct mb86a16_state *state,
		    unsigned char s1t,
		    unsigned s0t)
{
	if (mb86a16_write(state, 0x33, (s1t << 3) | s0t) < 0)
		goto err;

	return 0;
err:
	dprintk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	return -EREMOTEIO;
}
