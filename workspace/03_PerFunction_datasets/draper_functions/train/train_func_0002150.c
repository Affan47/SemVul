adv7183_writeregs(struct v4l2_subdev *sd,
		const unsigned char *regs, unsigned int num)
{
	unsigned char reg, data;
	unsigned int cnt = 0;

	if (num & 0x1) {
		v4l2_err(sd, "invalid regs array\n");
		return -1;
	}

	while (cnt < num) {
		reg = *regs++;
		data = *regs++;
		cnt += 2;

		adv7183_write(sd, reg, data);
	}
	return 0;
}
