gistgetadjusted(Relation r, IndexTuple oldtup, IndexTuple addtup, GISTSTATE *giststate)
{
	bool		neednew = FALSE;
	GISTENTRY	oldentries[INDEX_MAX_KEYS],
				addentries[INDEX_MAX_KEYS];
	bool		oldisnull[INDEX_MAX_KEYS],
				addisnull[INDEX_MAX_KEYS];
	IndexTuple	newtup = NULL;
	int			i;

	if (GistTupleIsInvalid(oldtup) || GistTupleIsInvalid(addtup))
		return gist_form_invalid_tuple(ItemPointerGetBlockNumber(&(oldtup->t_tid)));

	gistDeCompressAtt(giststate, r, oldtup, NULL,
					  (OffsetNumber) 0, oldentries, oldisnull);

	gistDeCompressAtt(giststate, r, addtup, NULL,
					  (OffsetNumber) 0, addentries, addisnull);

	for (i = 0; i < r->rd_att->natts; i++)
	{
		gistMakeUnionKey(giststate, i,
						 oldentries + i, oldisnull[i],
						 addentries + i, addisnull[i],
						 attrS + i, isnullS + i);

		if (neednew)

			continue;

		if (isnullS[i])

			continue;

		if (!addisnull[i])
		{
			if (oldisnull[i] || gistKeyIsEQ(giststate, i, oldentries[i].key, attrS[i]) == false)
				neednew = true;
		}
	}

	if (neednew)
	{

		newtup = gistFormTuple(giststate, r, attrS, isnullS, false);
		newtup->t_tid = oldtup->t_tid;
	}

	return newtup;
}
