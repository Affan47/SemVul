print_function_trftypes(StringInfo buf, HeapTuple proctup)
{
	Oid		   *trftypes;
	int			ntypes;

	ntypes = get_func_trftypes(proctup, &trftypes);
	if (ntypes > 0)
	{
		int			i;

		appendStringInfoString(buf, "\n TRANSFORM ");
		for (i = 0; i < ntypes; i++)
		{
			if (i != 0)
				appendStringInfoString(buf, ", ");
			appendStringInfo(buf, "FOR TYPE %s", format_type_be(trftypes[i]));
		}
	}
}
