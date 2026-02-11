alias_cb(enum grecs_callback_command cmd,
	 grecs_locus_t *locus,
	 void *varptr,
	 grecs_value_t *value,
	 void *cb_data)
{
    char **argv;
    int argc;
    int i;

    if (cmd != grecs_callback_set_value) {
	grecs_error(locus, 0, _("Unexpected block statement"));
	return 1;
    }
    if (value->type != GRECS_TYPE_ARRAY) {
	grecs_error(locus, 0, _("Not enough arguments for alias"));
	return 1;
    }
    argc = value->v.arg.c - 1;
    argv = xcalloc(argc + 1, sizeof(argv[0]));
    for (i = 0; i < argc; i++) {
	if (value->v.arg.v[i+1]->type != GRECS_TYPE_STRING) {
	    grecs_error(locus, 0, _("argument %d has wrong type"), i+1);
	    return 1;
	}
	argv[i] = xstrdup(value->v.arg.v[i+1]->v.string);
    }
    argv[i] = NULL;
    return alias_install(value->v.arg.v[0]->v.string, argc, argv, locus);
}
