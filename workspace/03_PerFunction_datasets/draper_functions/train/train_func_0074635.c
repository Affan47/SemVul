pch_i2c_init(struct i2c_algo_pch_data *adap)
{
	void __iomem *p = adap->pch_base_address;
	u32 pch_i2cbc;
	u32 pch_i2ctmr;
	u32 reg_value;


	iowrite32(0x01, p + PCH_I2CSRST);
	msleep(20);
	iowrite32(0x0, p + PCH_I2CSRST);


	iowrite32(0x21, p + PCH_I2CNF);

	pch_setbit(adap->pch_base_address, PCH_I2CCTL, PCH_I2CCTL_I2CMEN);

	if (pch_i2c_speed != 400)
		pch_i2c_speed = 100;

	reg_value = PCH_I2CCTL_I2CMEN;
	if (pch_i2c_speed == FAST_MODE_CLK) {
		reg_value |= FAST_MODE_EN;
		pch_dbg(adap, "Fast mode enabled\n");
	}

	if (pch_clk > PCH_MAX_CLK)
		pch_clk = 62500;

	pch_i2cbc = (pch_clk + (pch_i2c_speed * 4)) / (pch_i2c_speed * 8);

	iowrite32(pch_i2cbc, p + PCH_I2CBC);

	pch_i2ctmr = (pch_clk) / 8;
	iowrite32(pch_i2ctmr, p + PCH_I2CTMR);

	reg_value |= NORMAL_INTR_ENBL;
	iowrite32(reg_value, p + PCH_I2CCTL);

	pch_dbg(adap,
		"I2CCTL=%x pch_i2cbc=%x pch_i2ctmr=%x Enable interrupts\n",
		ioread32(p + PCH_I2CCTL), pch_i2cbc, pch_i2ctmr);

	init_waitqueue_head(&pch_event);
}
