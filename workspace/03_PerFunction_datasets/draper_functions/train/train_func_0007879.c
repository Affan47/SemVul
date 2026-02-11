random_slay(const bitflag mask[OF_SIZE])
{
	const struct slay *s_ptr;
	do {
		s_ptr = &slay_table[randint1(SL_MAX - 1)];
	} while (!of_has(mask, s_ptr->object_flag));

	return s_ptr;
}
