print_opt_section(const knot_opt_rr_t *rr)
{
	printf("Version: %u; flags: %s; UDP size: %u B\n",
	       knot_edns_get_version(rr),
	       (knot_edns_do(rr) != 0) ? "do" : "",
	       knot_edns_get_payload(rr));

	for (int i = 0; i < rr->option_count; i++) {
		knot_opt_option_t *opt = &(rr->options[i]);

		if (opt->code == EDNS_OPTION_NSID) {
			printf(";; NSID: ");
			short_hex_print(opt->data, opt->length);
			printf(";;     :  ");
			txt_print(opt->data, opt->length);
		} else {
			printf(";; Option (%u): ", opt->code);
			short_hex_print(opt->data, opt->length);
		}
	}
}
