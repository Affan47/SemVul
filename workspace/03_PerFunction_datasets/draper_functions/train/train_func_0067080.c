write_out_results(struct patch *list, int skipped_patch)
{
	int phase;
	int errs = 0;
	struct patch *l;

	if (!list && !skipped_patch)
		return error("No changes");

	for (phase = 0; phase < 2; phase++) {
		l = list;
		while (l) {
			if (l->rejected)
				errs = 1;
			else {
				write_out_one_result(l, phase);
				if (phase == 1 && write_out_one_reject(l))
					errs = 1;
			}
			l = l->next;
		}
	}
	return errs;
}
