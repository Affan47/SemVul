control_reg_sqmon(struct r8a66597 *r8a66597, u16 pipenum)
{
	unsigned long offset;

	if (pipenum == 0) {
		return r8a66597_read(r8a66597, DCPCTR) & SQMON;
	} else if (pipenum < R8A66597_MAX_NUM_PIPE) {
		offset = get_pipectr_addr(pipenum);
		return r8a66597_read(r8a66597, offset) & SQMON;
	} else {
		dev_err(r8a66597_to_dev(r8a66597),
			"unexpect pipe num(%d)\n", pipenum);
	}

	return 0;
}
