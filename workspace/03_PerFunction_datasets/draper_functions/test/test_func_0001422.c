GUCArrayAdd(ArrayType *array, const char *name, const char *value)
{
	struct config_generic *record;
	Datum		datum;
	char	   *newval;
	ArrayType  *a;

	Assert(name);
	Assert(value);


	(void) validate_option_array_item(name, value, false);


	record = find_option(name, false, WARNING);
	if (record)
		name = record->name;


	newval = psprintf("%s=%s", name, value);
	datum = CStringGetTextDatum(newval);

	if (array)
	{
		int			index;
		bool		isnull;
		int			i;

		Assert(ARR_ELEMTYPE(array) == TEXTOID);
		Assert(ARR_NDIM(array) == 1);
		Assert(ARR_LBOUND(array)[0] == 1);

		index = ARR_DIMS(array)[0] + 1;

		for (i = 1; i <= ARR_DIMS(array)[0]; i++)
		{
			Datum		d;
			char	   *current;

			d = array_ref(array, 1, &i,
						  -1  ,
						  -1  ,
						  false  ,
						  'i'  ,
						  &isnull);
			if (isnull)
				continue;
			current = TextDatumGetCString(d);


			if (strncmp(current, newval, strlen(name) + 1) == 0)
			{
				index = i;
				break;
			}
		}

		a = array_set(array, 1, &index,
					  datum,
					  false,
					  -1  ,
					  -1  ,
					  false  ,
					  'i'  );
	}
	else
		a = construct_array(&datum, 1,
							TEXTOID,
							-1, false, 'i');

	return a;
}
