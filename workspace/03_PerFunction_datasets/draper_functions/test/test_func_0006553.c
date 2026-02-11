knot_edns_free_options(knot_opt_rr_t *opt_rr)
{
	if (opt_rr->option_count > 0) {

		for (int i = 0; i < opt_rr->option_count; i++) {
			knot_opt_option_t *option = &(opt_rr->options[i]);
			free(option->data);
		}
		free(opt_rr->options);
	}
}
