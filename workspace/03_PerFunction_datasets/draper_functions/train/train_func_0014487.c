tproxy_tg_check(unsigned int flags)
{
	if (!(flags & PARAM_ONPORT))
		xtables_error(PARAMETER_PROBLEM,
			   "TPROXY target: Parameter --on-port is required");
}
