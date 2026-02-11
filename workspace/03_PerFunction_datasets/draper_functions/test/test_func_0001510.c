pch_i2c_cb(struct i2c_algo_pch_data *adap)
{
	u32 sts;
	void __iomem *p = adap->pch_base_address;

	sts = ioread32(p + PCH_I2CSR);
	sts &= (I2CMAL_BIT | I2CMCF_BIT | I2CMIF_BIT);
	if (sts & I2CMAL_BIT)
		adap->pch_event_flag |= I2CMAL_EVENT;

	if (sts & I2CMCF_BIT)
		adap->pch_event_flag |= I2CMCF_EVENT;


	pch_clrbit(adap->pch_base_address, PCH_I2CSR, sts);

	pch_dbg(adap, "PCH_I2CSR = %x\n", ioread32(p + PCH_I2CSR));

	wake_up(&pch_event);
}
