apol_mls_range_contain_subrange(const apol_policy_t * p, const apol_mls_range_t * range, const apol_mls_range_t * subrange)
{
	if (p == NULL || apol_mls_range_validate(p, subrange) != 1) {
		ERR(p, "%s", strerror(EINVAL));
		return -1;
	}


	if (apol_mls_range_does_include_level(p, range, subrange->low)) {
		if (subrange->high == NULL || apol_mls_range_does_include_level(p, range, subrange->high)) {
			return 1;
		}
	}
	return 0;
}
