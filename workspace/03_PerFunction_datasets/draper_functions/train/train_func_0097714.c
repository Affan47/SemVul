m5mols_set_wdr(struct m5mols_info *info, int wdr)
{
	int ret;

	ret = m5mols_write(&info->sd, MON_TONE_CTL, wdr ? 9 : 5);
	if (ret < 0)
		return ret;

	ret = m5mols_set_mode(info, REG_CAPTURE);
	if (ret < 0)
		return ret;

	return m5mols_write(&info->sd, CAPP_WDR_EN, wdr);
}
