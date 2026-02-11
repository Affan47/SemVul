smsc95xx_enter_suspend0(struct usbnet *dev)
{
	struct smsc95xx_priv *pdata = (struct smsc95xx_priv *)(dev->data[0]);
	u32 val;
	int ret;

	ret = smsc95xx_read_reg_nopm(dev, PM_CTRL, &val);
	if (ret < 0)
		return ret;

	val &= (~(PM_CTL_SUS_MODE_ | PM_CTL_WUPS_ | PM_CTL_PHY_RST_));
	val |= PM_CTL_SUS_MODE_0;

	ret = smsc95xx_write_reg_nopm(dev, PM_CTRL, val);
	if (ret < 0)
		return ret;


	val &= ~PM_CTL_WUPS_;
	val |= PM_CTL_WUPS_WOL_;


	if (pdata->wolopts & WAKE_PHY)
		val |= PM_CTL_WUPS_ED_;

	ret = smsc95xx_write_reg_nopm(dev, PM_CTRL, val);
	if (ret < 0)
		return ret;


	ret = smsc95xx_read_reg_nopm(dev, PM_CTRL, &val);
	if (ret < 0)
		return ret;

	pdata->suspend_flags |= SUSPEND_SUSPEND0;

	return 0;
}
