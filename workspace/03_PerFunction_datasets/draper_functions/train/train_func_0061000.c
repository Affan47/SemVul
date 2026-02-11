bond_opt_check_range(const struct bond_option *opt, u64 val)
{
	const struct bond_opt_value *minval, *maxval;

	minval = bond_opt_get_flags(opt, BOND_VALFLAG_MIN);
	maxval = bond_opt_get_flags(opt, BOND_VALFLAG_MAX);
	if (!maxval || (minval && val < minval->value) || val > maxval->value)
		return false;

	return true;
}
