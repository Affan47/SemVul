DirectFunctionCall5Coll(PGFunction func, Oid collation, Datum arg1, Datum arg2,
						Datum arg3, Datum arg4, Datum arg5)
{
	FunctionCallInfoData fcinfo;
	Datum		result;

	InitFunctionCallInfoData(fcinfo, NULL, 5, collation, NULL, NULL);

	fcinfo.arg[0] = arg1;
	fcinfo.arg[1] = arg2;
	fcinfo.arg[2] = arg3;
	fcinfo.arg[3] = arg4;
	fcinfo.arg[4] = arg5;
	fcinfo.argnull[0] = false;
	fcinfo.argnull[1] = false;
	fcinfo.argnull[2] = false;
	fcinfo.argnull[3] = false;
	fcinfo.argnull[4] = false;

	result = (*func) (&fcinfo);


	if (fcinfo.isnull)
		elog(ERROR, "function %p returned NULL", (void *) func);

	return result;
}
