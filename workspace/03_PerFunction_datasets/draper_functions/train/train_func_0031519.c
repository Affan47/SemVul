FunctionCall7(FmgrInfo *flinfo, Datum arg1, Datum arg2,
			  Datum arg3, Datum arg4, Datum arg5,
			  Datum arg6, Datum arg7)
{
	FunctionCallInfoData fcinfo;
	Datum		result;

	InitFunctionCallInfoData(fcinfo, flinfo, 7, NULL, NULL);

	fcinfo.arg[0] = arg1;
	fcinfo.arg[1] = arg2;
	fcinfo.arg[2] = arg3;
	fcinfo.arg[3] = arg4;
	fcinfo.arg[4] = arg5;
	fcinfo.arg[5] = arg6;
	fcinfo.arg[6] = arg7;
	fcinfo.argnull[0] = false;
	fcinfo.argnull[1] = false;
	fcinfo.argnull[2] = false;
	fcinfo.argnull[3] = false;
	fcinfo.argnull[4] = false;
	fcinfo.argnull[5] = false;
	fcinfo.argnull[6] = false;

	result = FunctionCallInvoke(&fcinfo);


	if (fcinfo.isnull)
		elog(ERROR, "function %u returned NULL", fcinfo.flinfo->fn_oid);

	return result;
}
