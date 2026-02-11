cmd_harden(const struct options *opt)
{
	struct cdok_puzzle puz;
	uint8_t solution[CDOK_CELLS];
	int r;

	if (read_puzzle(opt->in_file, &puz) < 0)
		return -1;

	r = cdok_solve(&puz, solution, NULL);
	if (r < 0) {
		fprintf(stderr, "Puzzle is not solvable\n");
		return -1;
	}

	if (r)
		fprintf(stderr, "warning: input grid solution is "
			"not unique\n");

	return do_harden(opt, solution, puz.size);
}
