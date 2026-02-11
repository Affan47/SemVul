max8997_rtc_enable_smpl(struct max8997_rtc_info *info, bool enable)
{
	int ret;
	u8 val, mask;

	if (!smpl_en)
		return;

	if (enable)
		val = (1 << SMPL_EN_SHIFT) | (0 << SMPLT_SHIFT);
	else
		val = 0;

	mask = SMPL_EN_MASK | SMPLT_MASK;

	dev_info(info->dev, "%s: %s SMPL\n", __func__,
			enable ? "enable" : "disable");

	ret = max8997_update_reg(info->rtc, MAX8997_RTC_WTSR_SMPL, val, mask);
	if (ret < 0) {
		dev_err(info->dev, "%s: fail to update SMPL reg(%d)\n",
				__func__, ret);
		return;
	}

	max8997_rtc_set_update_reg(info);

	val = 0;
	max8997_read_reg(info->rtc, MAX8997_RTC_WTSR_SMPL, &val);
	pr_info("WTSR_SMPL(0x%02x)\n", val);
}
