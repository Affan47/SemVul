SetSharedSecurityLabel(const ObjectAddress *object,
					   const char *provider, const char *label)
{
	Relation	pg_shseclabel;
	ScanKeyData keys[4];
	SysScanDesc scan;
	HeapTuple	oldtup;
	HeapTuple	newtup = NULL;
	Datum		values[Natts_pg_shseclabel];
	bool		nulls[Natts_pg_shseclabel];
	bool		replaces[Natts_pg_shseclabel];


	memset(nulls, false, sizeof(nulls));
	memset(replaces, false, sizeof(replaces));
	values[Anum_pg_shseclabel_objoid - 1] = ObjectIdGetDatum(object->objectId);
	values[Anum_pg_shseclabel_classoid - 1] = ObjectIdGetDatum(object->classId);
	values[Anum_pg_shseclabel_provider - 1] = CStringGetTextDatum(provider);
	if (label != NULL)
		values[Anum_pg_shseclabel_label - 1] = CStringGetTextDatum(label);


	ScanKeyInit(&keys[0],
				Anum_pg_shseclabel_objoid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(object->objectId));
	ScanKeyInit(&keys[1],
				Anum_pg_shseclabel_classoid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(object->classId));
	ScanKeyInit(&keys[2],
				Anum_pg_shseclabel_provider,
				BTEqualStrategyNumber, F_TEXTEQ,
				CStringGetTextDatum(provider));

	pg_shseclabel = heap_open(SharedSecLabelRelationId, RowExclusiveLock);

	scan = systable_beginscan(pg_shseclabel, SharedSecLabelObjectIndexId, true,
							  NULL, 3, keys);

	oldtup = systable_getnext(scan);
	if (HeapTupleIsValid(oldtup))
	{
		if (label == NULL)
			simple_heap_delete(pg_shseclabel, &oldtup->t_self);
		else
		{
			replaces[Anum_pg_shseclabel_label - 1] = true;
			newtup = heap_modify_tuple(oldtup, RelationGetDescr(pg_shseclabel),
									   values, nulls, replaces);
			simple_heap_update(pg_shseclabel, &oldtup->t_self, newtup);
		}
	}
	systable_endscan(scan);


	if (newtup == NULL && label != NULL)
	{
		newtup = heap_form_tuple(RelationGetDescr(pg_shseclabel),
								 values, nulls);
		simple_heap_insert(pg_shseclabel, newtup);
	}


	if (newtup != NULL)
	{
		CatalogUpdateIndexes(pg_shseclabel, newtup);
		heap_freetuple(newtup);
	}

	heap_close(pg_shseclabel, RowExclusiveLock);
}
