oid_array_to_list(Datum datum)
{
	ArrayType  *array = DatumGetArrayTypeP(datum);
	Datum	   *values;
	int			nelems;
	int			i;
	List	   *result = NIL;

	deconstruct_array(array,
					  OIDOID,
					  sizeof(Oid), true, 'i',
					  &values, NULL, &nelems);
	for (i = 0; i < nelems; i++)
		result = lappend_oid(result, values[i]);
	return result;
}
