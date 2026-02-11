index_reloptions(RegProcedure amoptions, Datum reloptions, bool validate)
{
	FmgrInfo	flinfo;
	FunctionCallInfoData fcinfo;
	Datum		result;

	Assert(RegProcedureIsValid(amoptions));


	if (reloptions == (Datum) 0)
		return NULL;


	fmgr_info(amoptions, &flinfo);

	InitFunctionCallInfoData(fcinfo, &flinfo, 2, NULL, NULL);

	fcinfo.arg[0] = reloptions;
	fcinfo.arg[1] = BoolGetDatum(validate);
	fcinfo.argnull[0] = false;
	fcinfo.argnull[1] = false;

	result = FunctionCallInvoke(&fcinfo);

	if (fcinfo.isnull || DatumGetPointer(result) == NULL)
		return NULL;

	return DatumGetByteaP(result);
}
