rll_dec(const rll_t *e, rllitr_t *itr, int *c, int is_free)
{
	int64_t l;
	if (*itr->q == 7) return -1;
	l = *itr->q>>3; *c = *itr->q&7;
	if (++itr->q - *itr->i == RLL_BLOCK_SIZE) {
		if (is_free) {
			free(*itr->i);
			*itr->i = 0;
		}
		itr->q = *++itr->i;
	}
	return l;
}
