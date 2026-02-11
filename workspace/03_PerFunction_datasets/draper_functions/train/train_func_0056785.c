def_prio_args_handler(vector strvec)
{
	conf->prio_args = set_value(strvec);

	if (!conf->prio_args)
		return 1;

	return 0;
}
