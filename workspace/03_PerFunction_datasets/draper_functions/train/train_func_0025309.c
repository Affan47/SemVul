bind_parse_name(char **args, int cur_arg, struct proxy *px, struct bind_conf *conf, char **err)
{
	struct listener *l;

	if (!*args[cur_arg + 1]) {
		memprintf(err, "'%s' : missing name", args[cur_arg]);
		return ERR_ALERT | ERR_FATAL;
	}

	list_for_each_entry(l, &conf->listeners, by_bind)
		l->name = strdup(args[cur_arg + 1]);

	return 0;
}
