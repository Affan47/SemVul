sca3000_reg_lock_on(struct sca3000_state *st)
{
	int ret;

	ret = sca3000_read_data_short(st, SCA3000_REG_ADDR_STATUS, 1);
	if (ret < 0)
		return ret;

	return !(st->rx[0] & SCA3000_LOCKED);
}
