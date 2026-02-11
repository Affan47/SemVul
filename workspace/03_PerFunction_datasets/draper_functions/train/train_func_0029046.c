cdok_generate(struct cdok_puzzle *puz,
		  const uint8_t *solution, int size,
		  cdok_flags_t fl, int iterations, int limit, int target)
{
	int best_score = 0;
	int i;

	if (size < 2)
		return 0;

	cdok_init_puzzle(puz, size);
	memcpy(puz->values, solution, sizeof(puz->values));

	for (i = 0; i < iterations; i++) {
		if (target > 0 && best_score >= target)
			break;

		best_score = harden(puz, solution, best_score, fl,
				    limit);
	}

	normalize_labels(puz);
	return best_score;
}
