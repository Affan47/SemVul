sum_candidates(int target, int size,
			     const uint8_t *members, int nm, int max)
{
	int partial_sum = 0;
	int i;

	for (i = 0; i < nm; i++)
		partial_sum += members[i];

	return addends_for(target - partial_sum, size - nm, max);
}
