varattnos_map(TupleDesc olddesc, TupleDesc newdesc)
{
	AttrNumber *attmap;
	int			i,
				j;

	attmap = (AttrNumber *) palloc0(sizeof(AttrNumber) * olddesc->natts);
	for (i = 1; i <= olddesc->natts; i++)
	{
		if (olddesc->attrs[i - 1]->attisdropped)
			continue;

		for (j = 1; j <= newdesc->natts; j++)
		{
			if (strcmp(NameStr(olddesc->attrs[i - 1]->attname),
					   NameStr(newdesc->attrs[j - 1]->attname)) == 0)
			{
				attmap[i - 1] = j;
				break;
			}
		}
	}
	return attmap;
}
