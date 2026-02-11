dnpds40_clear_counter(struct dnpds40_ctx *ctx, char counter)
{
	struct dnpds40_cmd cmd;
	char msg[4];
	int ret;


	dnpds40_build_cmd(&cmd, "MNT_WT", "COUNTER_CLEAR", 4);
	msg[0] = 'C';
	msg[1] = counter;
	msg[2] = 0x0d;
	msg[3] = 0x00;

	if ((ret = dnpds40_do_cmd(ctx, &cmd, (uint8_t*)msg, 4)))
		return ret;

	return 0;
}
