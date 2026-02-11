s5m8767_wait_for_udr_update(struct s5m_rtc_info *info)
{
	int ret, retry = UDR_READ_RETRY_CNT;
	unsigned int data;

	do {
		ret = regmap_read(info->regmap, info->regs->rtc_udr_update,
				&data);
	} while (--retry && (data & info->regs->rtc_udr_mask) && !ret);

	if (!retry)
		dev_err(info->dev, "waiting for UDR update, reached max number of retries\n");

	return ret;
}
