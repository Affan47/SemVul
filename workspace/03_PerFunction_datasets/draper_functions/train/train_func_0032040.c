pg_xlogfile_name_offset(PG_FUNCTION_ARGS)
{
	text	   *location = PG_GETARG_TEXT_P(0);
	char	   *locationstr;
	unsigned int uxlogid;
	unsigned int uxrecoff;
	uint32		xlogid;
	uint32		xlogseg;
	uint32		xrecoff;
	XLogRecPtr	locationpoint;
	char		xlogfilename[MAXFNAMELEN];
	Datum		values[2];
	bool		isnull[2];
	TupleDesc	resultTupleDesc;
	HeapTuple	resultHeapTuple;
	Datum		result;


	locationstr = DatumGetCString(DirectFunctionCall1(textout,
												 PointerGetDatum(location)));

	if (sscanf(locationstr, "%X/%X", &uxlogid, &uxrecoff) != 2)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("could not parse transaction log location \"%s\"",
						locationstr)));

	locationpoint.xlogid = uxlogid;
	locationpoint.xrecoff = uxrecoff;


	resultTupleDesc = CreateTemplateTupleDesc(2, false);
	TupleDescInitEntry(resultTupleDesc, (AttrNumber) 1, "file_name",
					   TEXTOID, -1, 0);
	TupleDescInitEntry(resultTupleDesc, (AttrNumber) 2, "file_offset",
					   INT4OID, -1, 0);

	resultTupleDesc = BlessTupleDesc(resultTupleDesc);


	XLByteToPrevSeg(locationpoint, xlogid, xlogseg);
	XLogFileName(xlogfilename, ThisTimeLineID, xlogid, xlogseg);

	values[0] = DirectFunctionCall1(textin,
									CStringGetDatum(xlogfilename));
	isnull[0] = false;


	xrecoff = locationpoint.xrecoff - xlogseg * XLogSegSize;

	values[1] = UInt32GetDatum(xrecoff);
	isnull[1] = false;


	resultHeapTuple = heap_form_tuple(resultTupleDesc, values, isnull);

	result = HeapTupleGetDatum(resultHeapTuple);

	PG_RETURN_DATUM(result);
}
