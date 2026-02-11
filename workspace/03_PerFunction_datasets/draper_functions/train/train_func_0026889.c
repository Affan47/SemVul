zswap_enabled_param_set(const char *val,
				   const struct kernel_param *kp)
{
	if (zswap_init_failed) {
		pr_err("can't enable, initialization failed\n");
		return -ENODEV;
	}

	return param_set_bool(val, kp);
}
