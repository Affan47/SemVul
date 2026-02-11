set_init_arg(char *param, char *val,
			       const char *unused, void *arg)
{
	unsigned int i;

	if (panic_later)
		return 0;

	repair_env_string(param, val, unused, NULL);

	for (i = 0; argv_init[i]; i++) {
		if (i == MAX_INIT_ARGS) {
			panic_later = "init";
			panic_param = param;
			return 0;
		}
	}
	argv_init[i] = param;
	return 0;
}
