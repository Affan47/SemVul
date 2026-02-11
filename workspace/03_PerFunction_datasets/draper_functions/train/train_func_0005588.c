BuildDescFromLists(List *names, List *types, List *typmods)
{
	int			natts;
	AttrNumber	attnum;
	ListCell   *l1;
	ListCell   *l2;
	ListCell   *l3;
	TupleDesc	desc;

	natts = list_length(names);
	Assert(natts == list_length(types));
	Assert(natts == list_length(typmods));


	desc = CreateTemplateTupleDesc(natts, false);

	attnum = 0;

	l2 = list_head(types);
	l3 = list_head(typmods);
	foreach(l1, names)
	{
		char	   *attname = strVal(lfirst(l1));
		Oid			atttypid;
		int32		atttypmod;

		atttypid = lfirst_oid(l2);
		l2 = lnext(l2);
		atttypmod = lfirst_int(l3);
		l3 = lnext(l3);

		attnum++;

		TupleDescInitEntry(desc, attnum, attname, atttypid, atttypmod, 0);
	}

	return desc;
}
