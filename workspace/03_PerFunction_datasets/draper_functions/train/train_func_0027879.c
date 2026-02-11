carl9170_set_hwretry_limit(struct ar9170 *ar, const unsigned int max_retry)
{
	u32 tmp = min_t(u32, 0x33333, max_retry * 0x11111);

	return carl9170_write_reg(ar, AR9170_MAC_REG_RETRY_MAX, tmp);
}
