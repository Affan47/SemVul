heap_tuple_attr_equals(TupleDesc tupdesc, int attrnum,
					   HeapTuple tup1, HeapTuple tup2)
{
	Datum		value1,
				value2;
	bool		isnull1,
				isnull2;
	Form_pg_attribute att;


	if (attrnum == 0)
		return false;


	if (attrnum < 0)
	{
		if (attrnum != ObjectIdAttributeNumber &&
			attrnum != TableOidAttributeNumber)
			return false;
	}


	value1 = heap_getattr(tup1, attrnum, tupdesc, &isnull1);
	value2 = heap_getattr(tup2, attrnum, tupdesc, &isnull2);


	if (isnull1 != isnull2)
		return false;


	if (isnull1)
		return true;


	if (attrnum <= 0)
	{

		return (DatumGetObjectId(value1) == DatumGetObjectId(value2));
	}
	else
	{
		Assert(attrnum <= tupdesc->natts);
		att = tupdesc->attrs[attrnum - 1];
		return datumIsEqual(value1, value2, att->attbyval, att->attlen);
	}
}
