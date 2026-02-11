pg_xlogfile_name(PG_FUNCTION_ARGS)
{
	text	   *location = PG_GETARG_TEXT_P(0);
	text	   *result;
	char	   *locationstr;
	unsigned int uxlogid;
	unsigned int uxrecoff;
	uint32		xlogid;
	uint32		xlogseg;
	XLogRecPtr	locationpoint;
	char		xlogfilename[MAXFNAMELEN];

	locationstr = DatumGetCString(DirectFunctionCall1(textout,
												 PointerGetDatum(location)));

	if (sscanf(locationstr, "%X/%X", &uxlogid, &uxrecoff) != 2)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("could not parse transaction log location \"%s\"",
						locationstr)));

	locationpoint.xlogid = uxlogid;
	locationpoint.xrecoff = uxrecoff;

	XLByteToPrevSeg(locationpoint, xlogid, xlogseg);
	XLogFileName(xlogfilename, ThisTimeLineID, xlogid, xlogseg);

	result = DatumGetTextP(DirectFunctionCall1(textin,
											 CStringGetDatum(xlogfilename)));
	PG_RETURN_TEXT_P(result);
}
