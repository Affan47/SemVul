_add_one_option(struct option **optz,
			   struct spank_plugin_opt *spopt)
{
	struct option opt;

	opt.name = spopt->opt->name;
	opt.has_arg = spopt->opt->has_arg;
	opt.flag = NULL;
	opt.val = spopt->optval;

	if (optz_add(optz, &opt) < 0) {
		if (errno == EEXIST) {
			error ("Ingoring conflicting option \"%s\" "
			       "in plugin \"%s\"",
			       opt.name, spopt->plugin->name);
		} else {
			error("Unable to add option \"%s\" "
			      "from plugin \"%s\"",
			      opt.name, spopt->plugin->name);
		}

		return (-1);
	}

	return (0);
}
