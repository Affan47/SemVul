calc_rank_or(float *w, TSVector t, TSQuery q)
{
	WordEntry  *entry,
			   *firstentry;
	WordEntryPos *post;
	int4		dimt,
				j,
				i,
				nitem;
	float		res = 0.0;
	QueryOperand **item;
	int			size = q->size;

	item = SortAndUniqItems(q, &size);

	for (i = 0; i < size; i++)
	{
		float		resj,
					wjm;
		int4		jm;

		firstentry = entry = find_wordentry(t, q, item[i], &nitem);
		if (!entry)
			continue;

		while (entry - firstentry < nitem)
		{
			if (entry->haspos)
			{
				dimt = POSDATALEN(t, entry);
				post = POSDATAPTR(t, entry);
			}
			else
			{
				dimt = POSNULL.npos;
				post = POSNULL.pos;
			}

			resj = 0.0;
			wjm = -1.0;
			jm = 0;
			for (j = 0; j < dimt; j++)
			{
				resj = resj + wpos(post[j]) / ((j + 1) * (j + 1));
				if (wpos(post[j]) > wjm)
				{
					wjm = wpos(post[j]);
					jm = j;
				}
			}


			res = res + (wjm + resj - wjm / ((jm + 1) * (jm + 1))) / 1.64493406685;

			entry++;
		}
	}
	if (size > 0)
		res = res / size;
	pfree(item);
	return res;
}
