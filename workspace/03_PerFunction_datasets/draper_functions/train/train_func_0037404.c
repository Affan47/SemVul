check_required(void)
{
    struct Option *opt;
    int err;

    err = 0;

    if (!n_opts)
	return (0);

    opt = &first_option;
    while (opt != NULL) {
	if (opt->required && opt->answer == NULL) {
	    fprintf(stderr,
		    _("ERROR: Required parameter <%s> not set:\n\t(%s)\n"),
		    opt->key, (opt->label ? opt->label : opt->description) );
	    err++;
	}
	opt = opt->next_opt;
    }

    return (err);
}
