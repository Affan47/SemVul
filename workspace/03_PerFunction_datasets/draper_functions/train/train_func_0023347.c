BuildDescFromLists(List *names, List *types, List *typmods, List *collations)
{
	int			natts;
	AttrNumber	attnum;
	ListCell   *l1;
	ListCell   *l2;
	ListCell   *l3;
	ListCell   *l4;
	TupleDesc	desc;

	natts = list_length(names);
	Assert(natts == list_length(types));
	Assert(natts == list_length(typmods));
	Assert(natts == list_length(collations));


	desc = CreateTemplateTupleDesc(natts, false);

	attnum = 0;

	l2 = list_head(types);
	l3 = list_head(typmods);
	l4 = list_head(collations);
	foreach(l1, names)
	{
		char	   *attname = strVal(lfirst(l1));
		Oid			atttypid;
		int32		atttypmod;
		Oid			attcollation;

		atttypid = lfirst_oid(l2);
		l2 = lnext(l2);
		atttypmod = lfirst_int(l3);
		l3 = lnext(l3);
		attcollation = lfirst_oid(l4);
		l4 = lnext(l4);

		attnum++;

		TupleDescInitEntry(desc, attnum, attname, atttypid, atttypmod, 0);
		TupleDescInitEntryCollation(desc, attnum, attcollation);
	}

	return desc;
}
