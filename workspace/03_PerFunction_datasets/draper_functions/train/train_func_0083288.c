inv_getsize(LargeObjectDesc *obj_desc)
{
	bool		found = false;
	uint32		lastbyte = 0;
	ScanKeyData skey[1];
	SysScanDesc sd;
	HeapTuple	tuple;

	Assert(PointerIsValid(obj_desc));

	open_lo_relation();

	ScanKeyInit(&skey[0],
				Anum_pg_largeobject_loid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(obj_desc->id));

	sd = systable_beginscan_ordered(lo_heap_r, lo_index_r,
									obj_desc->snapshot, 1, skey);


	while ((tuple = systable_getnext_ordered(sd, BackwardScanDirection)) != NULL)
	{
		Form_pg_largeobject data;
		bytea	   *datafield;
		bool		pfreeit;

		found = true;
		if (HeapTupleHasNulls(tuple))
			elog(ERROR, "null field found in pg_largeobject");
		data = (Form_pg_largeobject) GETSTRUCT(tuple);
		datafield = &(data->data);
		pfreeit = false;
		if (VARATT_IS_EXTENDED(datafield))
		{
			datafield = (bytea *)
				heap_tuple_untoast_attr((struct varlena *) datafield);
			pfreeit = true;
		}
		lastbyte = data->pageno * LOBLKSIZE + getbytealen(datafield);
		if (pfreeit)
			pfree(datafield);
		break;
	}

	systable_endscan_ordered(sd);

	if (!found)
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("large object %u does not exist", obj_desc->id)));
	return lastbyte;
}
