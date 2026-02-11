do_harden(const struct options *opt,
		     const uint8_t *solution, int size)

{
	struct cdok_puzzle puz;
	FILE *out;
	int r;

	r = cdok_generate(&puz, solution, size,
			  (opt->flags & OPT_FLAG_TWO_CELL) ?
			  CDOK_FLAGS_TWO_CELL : CDOK_FLAGS_NONE,
			  opt->gen_iterations,
			  opt->gen_limit,
			  opt->gen_target);

	out = open_output(opt->out_file);
	if (!out)
		return -1;

	write_puzzle(out, opt->flags, &puz, puz.values);
	fprintf(out, "\nDifficulty: %d\n", r);
	return close_output(opt->out_file, out);
}
