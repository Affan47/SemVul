_bt_mkscankey(Relation rel, IndexTuple itup)
{
	ScanKey		skey;
	TupleDesc	itupdesc;
	int			natts;
	int			i;

	itupdesc = RelationGetDescr(rel);
	natts = RelationGetNumberOfAttributes(rel);

	skey = (ScanKey) palloc(natts * sizeof(ScanKeyData));

	for (i = 0; i < natts; i++)
	{
		FmgrInfo   *procinfo;
		Datum		arg;
		bool		null;


		procinfo = index_getprocinfo(rel, i + 1, BTORDER_PROC);
		arg = index_getattr(itup, i + 1, itupdesc, &null);
		ScanKeyEntryInitializeWithInfo(&skey[i],
									   null ? SK_ISNULL : 0,
									   (AttrNumber) (i + 1),
									   InvalidStrategy,
									   InvalidOid,
									   procinfo,
									   arg);
	}

	return skey;
}
