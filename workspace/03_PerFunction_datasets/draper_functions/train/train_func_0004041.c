_afQueryLoop (int arg1, int arg2, int arg3, int arg4)
{
	if (arg2 < 0 || arg2 >= _AF_NUM_UNITS)
		return AU_NULL_PVLIST;

	switch (arg1)
	{
		case AF_QUERY_SUPPORTED:
			return _af_pv_long(_af_units[arg2].loopPerInstrumentCount != 0);
		case AF_QUERY_MAX_NUMBER:
			return _af_pv_long(_af_units[arg2].loopPerInstrumentCount);
	}

	_af_error(AF_BAD_QUERY, "bad query selector");
	return AU_NULL_PVLIST;
}
