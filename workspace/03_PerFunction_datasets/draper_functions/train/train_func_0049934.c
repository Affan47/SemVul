gettype(char *type)
{
	int			i;
	Relation	rel;
	HeapScanDesc scan;
	HeapTuple	tup;
	struct typmap **app;

	if (Typ != NULL)
	{
		for (app = Typ; *app != NULL; app++)
		{
			if (strncmp(NameStr((*app)->am_typ.typname), type, NAMEDATALEN) == 0)
			{
				Ap = *app;
				return (*app)->am_oid;
			}
		}
	}
	else
	{
		for (i = 0; i < n_types; i++)
		{
			if (strncmp(type, TypInfo[i].name, NAMEDATALEN) == 0)
				return i;
		}
		elog(DEBUG4, "external type: %s", type);
		rel = heap_open(TypeRelationId, NoLock);
		scan = heap_beginscan(rel, SnapshotNow, 0, NULL);
		i = 0;
		while ((tup = heap_getnext(scan, ForwardScanDirection)) != NULL)
			++i;
		heap_endscan(scan);
		app = Typ = ALLOC(struct typmap *, i + 1);
		while (i-- > 0)
			*app++ = ALLOC(struct typmap, 1);
		*app = NULL;
		scan = heap_beginscan(rel, SnapshotNow, 0, NULL);
		app = Typ;
		while ((tup = heap_getnext(scan, ForwardScanDirection)) != NULL)
		{
			(*app)->am_oid = HeapTupleGetOid(tup);
			memmove((char *) &(*app++)->am_typ,
					(char *) GETSTRUCT(tup),
					sizeof((*app)->am_typ));
		}
		heap_endscan(scan);
		heap_close(rel, NoLock);
		return gettype(type);
	}
	elog(ERROR, "unrecognized type \"%s\"", type);

	return 0;
}
