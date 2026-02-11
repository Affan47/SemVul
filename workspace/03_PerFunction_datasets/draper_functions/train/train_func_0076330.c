control_reg_get(struct r8a66597 *r8a66597, u16 pipenum)
{
	u16 ret = 0;
	unsigned long offset;

	if (pipenum == 0) {
		ret = r8a66597_read(r8a66597, DCPCTR);
	} else if (pipenum < R8A66597_MAX_NUM_PIPE) {
		offset = get_pipectr_addr(pipenum);
		ret = r8a66597_read(r8a66597, offset);
	} else {
		dev_err(r8a66597_to_dev(r8a66597), "unexpect pipe num (%d)\n",
			pipenum);
	}

	return ret;
}
