xgbe_read_mmd_regs(struct xgbe_prv_data *pdata, int prtad,
			      int mmd_reg)
{
	unsigned int mmd_address;
	int mmd_data;

	if (mmd_reg & MII_ADDR_C45)
		mmd_address = mmd_reg & ~MII_ADDR_C45;
	else
		mmd_address = (pdata->mdio_mmd << 16) | (mmd_reg & 0xffff);


	mutex_lock(&pdata->xpcs_mutex);
	XPCS_IOWRITE(pdata, PCS_MMD_SELECT << 2, mmd_address >> 8);
	mmd_data = XPCS_IOREAD(pdata, (mmd_address & 0xff) << 2);
	mutex_unlock(&pdata->xpcs_mutex);

	return mmd_data;
}
