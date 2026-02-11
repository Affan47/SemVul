apol_mls_range_set_high(const apol_policy_t * p, apol_mls_range_t * range, apol_mls_level_t * level)
{
	if (!range) {
		ERR(p, "%s", strerror(EINVAL));
		errno = EINVAL;
		return -1;
	}

	if (range->high != level) {
		if (range->low != range->high) {
			apol_mls_level_destroy(&(range->high));
		}
		range->high = level;
	}
	return 0;
}
