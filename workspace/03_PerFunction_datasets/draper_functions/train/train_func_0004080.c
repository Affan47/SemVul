grouped_arg_str_value(const struct arg_values *av, int a, const char *def)
{
	return grouped_arg_count(av, a) ? av[a].value : def;
}
