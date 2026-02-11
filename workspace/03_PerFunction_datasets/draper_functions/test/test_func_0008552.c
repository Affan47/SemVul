OperatorShellMake(const char *operatorName,
				  Oid operatorNamespace,
				  Oid leftTypeId,
				  Oid rightTypeId)
{
	Relation	pg_operator_desc;
	Oid			operatorObjectId;
	int			i;
	HeapTuple	tup;
	Datum		values[Natts_pg_operator];
	char		nulls[Natts_pg_operator];
	NameData	oname;
	TupleDesc	tupDesc;


	if (!validOperatorName(operatorName))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_NAME),
				 errmsg("\"%s\" is not a valid operator name",
						operatorName)));


	for (i = 0; i < Natts_pg_operator; ++i)
	{
		nulls[i] = ' ';
		values[i] = (Datum) NULL;
	}


	i = 0;
	namestrcpy(&oname, operatorName);
	values[i++] = NameGetDatum(&oname);
	values[i++] = ObjectIdGetDatum(operatorNamespace);
	values[i++] = ObjectIdGetDatum(GetUserId());
	values[i++] = CharGetDatum(leftTypeId ? (rightTypeId ? 'b' : 'r') : 'l');
	values[i++] = BoolGetDatum(false);
	values[i++] = ObjectIdGetDatum(leftTypeId);
	values[i++] = ObjectIdGetDatum(rightTypeId);
	values[i++] = ObjectIdGetDatum(InvalidOid);
	values[i++] = ObjectIdGetDatum(InvalidOid);
	values[i++] = ObjectIdGetDatum(InvalidOid);
	values[i++] = ObjectIdGetDatum(InvalidOid);
	values[i++] = ObjectIdGetDatum(InvalidOid);
	values[i++] = ObjectIdGetDatum(InvalidOid);
	values[i++] = ObjectIdGetDatum(InvalidOid);
	values[i++] = ObjectIdGetDatum(InvalidOid);
	values[i++] = ObjectIdGetDatum(InvalidOid);
	values[i++] = ObjectIdGetDatum(InvalidOid);


	pg_operator_desc = heap_open(OperatorRelationId, RowExclusiveLock);
	tupDesc = pg_operator_desc->rd_att;


	tup = heap_formtuple(tupDesc, values, nulls);


	operatorObjectId = simple_heap_insert(pg_operator_desc, tup);

	CatalogUpdateIndexes(pg_operator_desc, tup);


	makeOperatorDependencies(tup);

	heap_freetuple(tup);


	heap_close(pg_operator_desc, RowExclusiveLock);

	return operatorObjectId;
}
