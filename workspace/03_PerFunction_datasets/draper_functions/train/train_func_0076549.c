ri_KeysEqual(Relation rel, HeapTuple oldtup, HeapTuple newtup,
			 const RI_ConstraintInfo *riinfo, bool rel_is_pk)
{
	TupleDesc	tupdesc = RelationGetDescr(rel);
	const int16 *attnums;
	const Oid  *eq_oprs;
	int			i;

	if (rel_is_pk)
	{
		attnums = riinfo->pk_attnums;
		eq_oprs = riinfo->pp_eq_oprs;
	}
	else
	{
		attnums = riinfo->fk_attnums;
		eq_oprs = riinfo->ff_eq_oprs;
	}

	for (i = 0; i < riinfo->nkeys; i++)
	{
		Datum		oldvalue;
		Datum		newvalue;
		bool		isnull;


		oldvalue = heap_getattr(oldtup, attnums[i], tupdesc, &isnull);
		if (isnull)
			return false;


		newvalue = heap_getattr(newtup, attnums[i], tupdesc, &isnull);
		if (isnull)
			return false;


		if (!ri_AttributesEqual(eq_oprs[i], RIAttType(rel, attnums[i]),
								oldvalue, newvalue))
			return false;
	}

	return true;
}
