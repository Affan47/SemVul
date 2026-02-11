riic_xfer(struct i2c_adapter *adap, struct i2c_msg msgs[], int num)
{
	struct riic_dev *riic = i2c_get_adapdata(adap);
	unsigned long time_left;
	int i, ret;
	u8 start_bit;

	ret = clk_prepare_enable(riic->clk);
	if (ret)
		return ret;

	if (readb(riic->base + RIIC_ICCR2) & ICCR2_BBSY) {
		riic->err = -EBUSY;
		goto out;
	}

	reinit_completion(&riic->msg_done);
	riic->err = 0;

	writeb(0, riic->base + RIIC_ICSR2);

	for (i = 0, start_bit = ICCR2_ST; i < num; i++) {
		riic->bytes_left = RIIC_INIT_MSG;
		riic->buf = msgs[i].buf;
		riic->msg = &msgs[i];
		riic->is_last = (i == num - 1);

		writeb(ICIER_NAKIE | ICIER_TIE, riic->base + RIIC_ICIER);

		writeb(start_bit, riic->base + RIIC_ICCR2);

		time_left = wait_for_completion_timeout(&riic->msg_done, riic->adapter.timeout);
		if (time_left == 0)
			riic->err = -ETIMEDOUT;

		if (riic->err)
			break;

		start_bit = ICCR2_RS;
	}

 out:
	clk_disable_unprepare(riic->clk);

	return riic->err ?: num;
}
