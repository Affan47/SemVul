ParseVariableNum(const char *val,
				 int defaultval,
				 int faultval,
				 bool allowtrail)
{
	int			result;

	if (!val)
		result = defaultval;
	else if (!val[0])
		result = faultval;
	else
	{
		char	   *end;

		result = strtol(val, &end, 0);
		if (!allowtrail && *end)
			result = faultval;
	}

	return result;
}
