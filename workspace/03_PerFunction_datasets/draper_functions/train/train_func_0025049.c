opt_parse_track(const struct option *opt, const char *arg, int not)
{
	struct string_list *list = opt->value;
	if (not)
		string_list_clear(list, 0);
	else
		string_list_append(list, arg);
	return 0;
}
