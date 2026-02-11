StoreAttrDefault(Relation rel, AttrNumber attnum, char *adbin)
{
	Node	   *expr;
	char	   *adsrc;
	Relation	adrel;
	HeapTuple	tuple;
	Datum		values[4];
	static char nulls[4] = {' ', ' ', ' ', ' '};
	Relation	attrrel;
	HeapTuple	atttup;
	Form_pg_attribute attStruct;
	Oid			attrdefOid;
	ObjectAddress colobject,
				defobject;


	expr = stringToNode(adbin);


	adsrc = deparse_expression(expr,
							deparse_context_for(RelationGetRelationName(rel),
												RelationGetRelid(rel)),
							   false, false);


	values[Anum_pg_attrdef_adrelid - 1] = RelationGetRelid(rel);
	values[Anum_pg_attrdef_adnum - 1] = attnum;
	values[Anum_pg_attrdef_adbin - 1] = DirectFunctionCall1(textin,
													 CStringGetDatum(adbin));
	values[Anum_pg_attrdef_adsrc - 1] = DirectFunctionCall1(textin,
													 CStringGetDatum(adsrc));

	adrel = heap_open(AttrDefaultRelationId, RowExclusiveLock);

	tuple = heap_formtuple(adrel->rd_att, values, nulls);
	attrdefOid = simple_heap_insert(adrel, tuple);

	CatalogUpdateIndexes(adrel, tuple);

	defobject.classId = AttrDefaultRelationId;
	defobject.objectId = attrdefOid;
	defobject.objectSubId = 0;

	heap_close(adrel, RowExclusiveLock);


	pfree(DatumGetPointer(values[Anum_pg_attrdef_adbin - 1]));
	pfree(DatumGetPointer(values[Anum_pg_attrdef_adsrc - 1]));
	heap_freetuple(tuple);
	pfree(adsrc);


	attrrel = heap_open(AttributeRelationId, RowExclusiveLock);
	atttup = SearchSysCacheCopy(ATTNUM,
								ObjectIdGetDatum(RelationGetRelid(rel)),
								Int16GetDatum(attnum),
								0, 0);
	if (!HeapTupleIsValid(atttup))
		elog(ERROR, "cache lookup failed for attribute %d of relation %u",
			 attnum, RelationGetRelid(rel));
	attStruct = (Form_pg_attribute) GETSTRUCT(atttup);
	if (!attStruct->atthasdef)
	{
		attStruct->atthasdef = true;
		simple_heap_update(attrrel, &atttup->t_self, atttup);

		CatalogUpdateIndexes(attrrel, atttup);
	}
	heap_close(attrrel, RowExclusiveLock);
	heap_freetuple(atttup);


	colobject.classId = RelationRelationId;
	colobject.objectId = RelationGetRelid(rel);
	colobject.objectSubId = attnum;

	recordDependencyOn(&defobject, &colobject, DEPENDENCY_AUTO);


	recordDependencyOnExpr(&defobject, expr, NIL, DEPENDENCY_NORMAL);
}
