cm32181_read_als_it(struct cm32181_chip *cm32181, int *val2)
{
	u16 als_it;
	int i;

	als_it = cm32181->conf_regs[CM32181_REG_ADDR_CMD];
	als_it &= CM32181_CMD_ALS_IT_MASK;
	als_it >>= CM32181_CMD_ALS_IT_SHIFT;
	for (i = 0; i < ARRAY_SIZE(als_it_bits); i++) {
		if (als_it == als_it_bits[i]) {
			*val2 = als_it_value[i];
			return IIO_VAL_INT_PLUS_MICRO;
		}
	}

	return -EINVAL;
}
