apol_query_set_flag(const apol_policy_t * p __attribute__ ((unused)), unsigned int *flags, const int is_flag, int flag_value)
{
	if (is_flag) {
		*flags |= flag_value;
	} else {
		*flags &= ~flag_value;
	}
	return 0;
}
