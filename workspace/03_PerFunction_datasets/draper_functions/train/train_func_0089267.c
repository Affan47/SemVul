check_range(struct da903x_regulator_info *info,
				int min_uV, int max_uV)
{
	if (min_uV < info->desc.min_uV || min_uV > info->max_uV)
		return -EINVAL;

	return 0;
}
