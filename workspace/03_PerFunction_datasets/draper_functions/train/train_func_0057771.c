compatible_tupdesc(TupleDesc td1, TupleDesc td2)
{
	int			i;

	if (td1->natts != td2->natts)
		return false;

	for (i = 0; i < td1->natts; i++)
	{
		if (td1->attrs[i]->atttypid != td2->attrs[i]->atttypid)
			return false;
	}

	return true;
}
