AddNewAttributeTuples(Oid new_rel_oid,
					  TupleDesc tupdesc,
					  char relkind,
					  bool oidislocal,
					  int oidinhcount)
{
	Form_pg_attribute attr;
	int			i;
	Relation	rel;
	CatalogIndexState indstate;
	int			natts = tupdesc->natts;
	ObjectAddress myself,
				referenced;


	rel = heap_open(AttributeRelationId, RowExclusiveLock);

	indstate = CatalogOpenIndexes(rel);


	for (i = 0; i < natts; i++)
	{
		attr = tupdesc->attrs[i];

		attr->attrelid = new_rel_oid;

		attr->attstattarget = -1;
		attr->attcacheoff = -1;

		InsertPgAttributeTuple(rel, attr, indstate);


		myself.classId = RelationRelationId;
		myself.objectId = new_rel_oid;
		myself.objectSubId = i + 1;
		referenced.classId = TypeRelationId;
		referenced.objectId = attr->atttypid;
		referenced.objectSubId = 0;
		recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);
	}


	if (relkind != RELKIND_VIEW && relkind != RELKIND_COMPOSITE_TYPE)
	{
		for (i = 0; i < (int) lengthof(SysAtt); i++)
		{
			FormData_pg_attribute attStruct;


			if (!tupdesc->tdhasoid &&
				SysAtt[i]->attnum == ObjectIdAttributeNumber)
				continue;

			memcpy(&attStruct, (char *) SysAtt[i], sizeof(FormData_pg_attribute));


			attStruct.attrelid = new_rel_oid;


			if (attStruct.attnum == ObjectIdAttributeNumber)
			{
				attStruct.attislocal = oidislocal;
				attStruct.attinhcount = oidinhcount;
			}

			InsertPgAttributeTuple(rel, &attStruct, indstate);
		}
	}


	CatalogCloseIndexes(indstate);

	heap_close(rel, RowExclusiveLock);
}
