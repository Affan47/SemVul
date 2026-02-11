CopyOneRowTo(CopyState cstate, Oid tupleOid, Datum *values, bool *nulls)
{
	bool		need_delim = false;
	FmgrInfo   *out_functions = cstate->out_functions;
	MemoryContext oldcontext;
	ListCell   *cur;
	char	   *string;

	MemoryContextReset(cstate->rowcontext);
	oldcontext = MemoryContextSwitchTo(cstate->rowcontext);

	if (cstate->binary)
	{

		CopySendInt16(cstate, list_length(cstate->attnumlist));

		if (cstate->oids)
		{

			CopySendInt32(cstate, sizeof(int32));
			CopySendInt32(cstate, tupleOid);
		}
	}
	else
	{


		if (cstate->oids)
		{
			string = DatumGetCString(DirectFunctionCall1(oidout,
												ObjectIdGetDatum(tupleOid)));
			CopySendString(cstate, string);
			need_delim = true;
		}
	}

	foreach(cur, cstate->attnumlist)
	{
		int			attnum = lfirst_int(cur);
		Datum		value = values[attnum - 1];
		bool		isnull = nulls[attnum - 1];

		if (!cstate->binary)
		{
			if (need_delim)
				CopySendChar(cstate, cstate->delim[0]);
			need_delim = true;
		}

		if (isnull)
		{
			if (!cstate->binary)
				CopySendString(cstate, cstate->null_print_client);
			else
				CopySendInt32(cstate, -1);
		}
		else
		{
			if (!cstate->binary)
			{
				string = OutputFunctionCall(&out_functions[attnum - 1],
											value);
				if (cstate->csv_mode)
					CopyAttributeOutCSV(cstate, string,
										cstate->force_quote_flags[attnum - 1],
										list_length(cstate->attnumlist) == 1);
				else
					CopyAttributeOutText(cstate, string);
			}
			else
			{
				bytea	   *outputbytes;

				outputbytes = SendFunctionCall(&out_functions[attnum - 1],
											   value);
				CopySendInt32(cstate, VARSIZE(outputbytes) - VARHDRSZ);
				CopySendData(cstate, VARDATA(outputbytes),
							 VARSIZE(outputbytes) - VARHDRSZ);
			}
		}
	}

	CopySendEndOfRow(cstate);

	MemoryContextSwitchTo(oldcontext);

	cstate->processed++;
}
