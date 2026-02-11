add_candidate(int seq, int cand, char dir, mer_t min, short loc1, short loc2)
{


	if (!should_compare_cands(seq, cand)) return;

	int index = (seq*cand*499);
	if (index < 0) { index *= -1; }
	index = index % CAND_TABLE_BUCKETS;

	cand_list_element * cle = candidates[index];

	if (!cle)
	{
		candidates[index] = create_new_cle(seq, cand, dir, loc1, loc2);

		total_cand++;
		return;
	}


	while (cle)
	{
		if ((cle->cand1 == seq) && (cle->cand2 == cand) && (cle->dir == dir))
		{
			cle->count++;
			return;
		}
		else if ((cle->cand2 == seq) && (cle->cand1 == cand) && (cle->dir == dir))
		{
			cle->count++;
			return;
		}
		cle = cle->next;
	}


	cand_list_element * new_cle = create_new_cle(seq, cand, dir, loc1, loc2);
	new_cle->next = candidates[index];
	candidates[index] = new_cle;
	total_cand++;
	return;

}
