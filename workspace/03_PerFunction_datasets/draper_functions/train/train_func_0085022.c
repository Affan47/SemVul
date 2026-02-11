FunctionCall2(FmgrInfo *flinfo, Datum arg1, Datum arg2)
{


	FunctionCallInfoData fcinfo;
	Datum		result;

	InitFunctionCallInfoData(fcinfo, flinfo, 2, NULL, NULL);

	fcinfo.arg[0] = arg1;
	fcinfo.arg[1] = arg2;
	fcinfo.argnull[0] = false;
	fcinfo.argnull[1] = false;

	result = FunctionCallInvoke(&fcinfo);


	if (fcinfo.isnull)
		elog(ERROR, "function %u returned NULL", fcinfo.flinfo->fn_oid);

	return result;
}
