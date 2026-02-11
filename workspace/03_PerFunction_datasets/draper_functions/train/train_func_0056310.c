best_target(const struct lbalance *lb)
{
	unsigned int i, best = 0, found_drop = 0;
	float best_f_max = -1.0, cliff = -1.0;

#if 0
	for (i = 1; i < lb->max_stats; i++) {
		printf("%u: %f (%u)\n", i,
		       lb->stats[i].work_rate / lb->stats[i].num_stats,
		       lb->stats[i].num_stats);
	}
#endif

	for (i = 1; i < lb->max_stats; i++) {
		float f;

		if (!lb->stats[i].num_stats)
			f = 0;
		else
			f = lb->stats[i].work_rate / lb->stats[i].num_stats;

		if (f > best_f_max) {
#if 0
			printf("Best is %i\n", i);
#endif
			best_f_max = f - (f / (i + 1)) / 4;
			cliff = f - (f / (i + 1)) / 2;
			best = i;
			found_drop = 0;
		} else if (!found_drop && f < cliff) {
#if 0
			printf("Found drop at %i\n", i);
#endif
			found_drop = i;
		}
	}

	if (found_drop) {
		return found_drop - 1;
	}
	return i - 1;
}
