zd_rfwritev_locked(struct zd_chip *chip,
	               const u32* values, unsigned int count, u8 bits)
{
	int r;
	unsigned int i;

	for (i = 0; i < count; i++) {
		r = zd_rfwrite_locked(chip, values[i], bits);
		if (r)
			return r;
	}

	return 0;
}
