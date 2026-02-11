__rep_stat_print(env, flags)
	ENV *env;
	u_int32_t flags;
{
	u_int32_t orig_flags;
	int ret;

	orig_flags = flags;
	LF_CLR(DB_STAT_CLEAR | DB_STAT_SUBSYSTEM);
	if (LF_ISSET(DB_STAT_SUMMARY))
		return (__rep_stat_summary_print(env));

	if (flags == 0 || LF_ISSET(DB_STAT_ALL)) {
		ret = __rep_print_stats(env, orig_flags);
		if (flags == 0 || ret != 0)
			return (ret);
	}

	if (LF_ISSET(DB_STAT_ALL) &&
	    (ret = __rep_print_all(env, orig_flags)) != 0)
		return (ret);

	return (0);
}
