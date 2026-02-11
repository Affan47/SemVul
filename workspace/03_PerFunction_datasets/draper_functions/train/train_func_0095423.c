xtables_option_tpcall(unsigned int c, char **argv, bool invert,
			   struct xtables_target *t, void *fw)
{
	struct xt_option_call cb;

	if (t->x6_parse == NULL) {
		if (t->parse != NULL)
			t->parse(c - t->option_offset, argv, invert,
				 &t->tflags, fw, &t->t);
		return;
	}

	c -= t->option_offset;
	cb.entry = xtables_option_lookup(t->x6_options, c);
	if (cb.entry == NULL)
		xtables_error(OTHER_PROBLEM,
			"Extension does not know id %u\n", c);
	cb.arg      = optarg;
	cb.invert   = invert;
	cb.ext_name = t->name;
	cb.data     = t->t->data;
	cb.xflags   = t->tflags;
	t->x6_parse(&cb);
	t->tflags = cb.xflags;
}
