MergeConstraintsIntoExisting(Relation child_rel, Relation parent_rel)
{
	Relation	catalog_relation;
	TupleDesc	tuple_desc;
	SysScanDesc parent_scan;
	ScanKeyData parent_key;
	HeapTuple	parent_tuple;

	catalog_relation = heap_open(ConstraintRelationId, RowExclusiveLock);
	tuple_desc = RelationGetDescr(catalog_relation);


	ScanKeyInit(&parent_key,
				Anum_pg_constraint_conrelid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(RelationGetRelid(parent_rel)));
	parent_scan = systable_beginscan(catalog_relation, ConstraintRelidIndexId,
									 true, SnapshotNow, 1, &parent_key);

	while (HeapTupleIsValid(parent_tuple = systable_getnext(parent_scan)))
	{
		Form_pg_constraint parent_con = (Form_pg_constraint) GETSTRUCT(parent_tuple);
		SysScanDesc child_scan;
		ScanKeyData child_key;
		HeapTuple	child_tuple;
		bool		found = false;

		if (parent_con->contype != CONSTRAINT_CHECK)
			continue;


		ScanKeyInit(&child_key,
					Anum_pg_constraint_conrelid,
					BTEqualStrategyNumber, F_OIDEQ,
					ObjectIdGetDatum(RelationGetRelid(child_rel)));
		child_scan = systable_beginscan(catalog_relation, ConstraintRelidIndexId,
										true, SnapshotNow, 1, &child_key);

		while (HeapTupleIsValid(child_tuple = systable_getnext(child_scan)))
		{
			Form_pg_constraint child_con = (Form_pg_constraint) GETSTRUCT(child_tuple);
			HeapTuple	child_copy;

			if (child_con->contype != CONSTRAINT_CHECK)
				continue;

			if (strcmp(NameStr(parent_con->conname),
					   NameStr(child_con->conname)) != 0)
				continue;

			if (!constraints_equivalent(parent_tuple, child_tuple, tuple_desc))
				ereport(ERROR,
						(errcode(ERRCODE_DATATYPE_MISMATCH),
						 errmsg("child table \"%s\" has different definition for check constraint \"%s\"",
								RelationGetRelationName(child_rel),
								NameStr(parent_con->conname))));


			child_copy = heap_copytuple(child_tuple);
			child_con = (Form_pg_constraint) GETSTRUCT(child_copy);
			child_con->coninhcount++;
			simple_heap_update(catalog_relation, &child_copy->t_self, child_copy);
			CatalogUpdateIndexes(catalog_relation, child_copy);
			heap_freetuple(child_copy);

			found = true;
			break;
		}

		systable_endscan(child_scan);

		if (!found)
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("child table is missing constraint \"%s\"",
							NameStr(parent_con->conname))));
	}

	systable_endscan(parent_scan);
	heap_close(catalog_relation, RowExclusiveLock);
}
