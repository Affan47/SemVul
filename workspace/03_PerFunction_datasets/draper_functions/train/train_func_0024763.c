omap_hsmmc_disable_boot_regulator(struct regulator *reg)
{
	int ret;

	if (!reg)
		return 0;

	if (regulator_is_enabled(reg)) {
		ret = regulator_enable(reg);
		if (ret)
			return ret;

		ret = regulator_disable(reg);
		if (ret)
			return ret;
	}

	return 0;
}
