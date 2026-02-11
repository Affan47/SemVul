OidFunctionCall8(Oid functionId, Datum arg1, Datum arg2,
				 Datum arg3, Datum arg4, Datum arg5,
				 Datum arg6, Datum arg7, Datum arg8)
{
	FmgrInfo	flinfo;
	FunctionCallInfoData fcinfo;
	Datum		result;

	fmgr_info(functionId, &flinfo);

	InitFunctionCallInfoData(fcinfo, &flinfo, 8, NULL, NULL);

	fcinfo.arg[0] = arg1;
	fcinfo.arg[1] = arg2;
	fcinfo.arg[2] = arg3;
	fcinfo.arg[3] = arg4;
	fcinfo.arg[4] = arg5;
	fcinfo.arg[5] = arg6;
	fcinfo.arg[6] = arg7;
	fcinfo.arg[7] = arg8;
	fcinfo.argnull[0] = false;
	fcinfo.argnull[1] = false;
	fcinfo.argnull[2] = false;
	fcinfo.argnull[3] = false;
	fcinfo.argnull[4] = false;
	fcinfo.argnull[5] = false;
	fcinfo.argnull[6] = false;
	fcinfo.argnull[7] = false;

	result = FunctionCallInvoke(&fcinfo);


	if (fcinfo.isnull)
		elog(ERROR, "function %u returned NULL", flinfo.fn_oid);

	return result;
}
