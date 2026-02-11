_afQueryInstrument (int arg1, int arg2, int arg3, int arg4)
{
	switch (arg1)
	{
		case AF_QUERY_SUPPORTED:
			if (arg2 < 0 || arg2 >= _AF_NUM_UNITS)
				return AU_NULL_PVLIST;
			return _af_pv_long(_af_units[arg2].instrumentCount != 0);

		case AF_QUERY_MAX_NUMBER:
			if (arg2 < 0 || arg2 >= _AF_NUM_UNITS)
				return AU_NULL_PVLIST;
			return _af_pv_long(_af_units[arg2].instrumentCount);
	}

	_af_error(AF_BAD_QUERY, "bad query selector");
	return AU_NULL_PVLIST;
}
