errstart(int elevel, const char *filename, int lineno,
		 const char *funcname)
{
	ErrorData  *edata;
	bool		output_to_server;
	bool		output_to_client = false;
	int			i;


	if (elevel >= ERROR)
	{


		if (CritSectionCount > 0)
			elevel = PANIC;


		if (elevel == ERROR)
		{
			if (PG_exception_stack == NULL ||
				ExitOnAnyError ||
				proc_exit_inprogress)
				elevel = FATAL;
		}


		for (i = 0; i <= errordata_stack_depth; i++)
			elevel = Max(elevel, errordata[i].elevel);
	}


	if (IsPostmasterEnvironment)
		output_to_server = is_log_level_output(elevel, log_min_messages);
	else

		output_to_server = (elevel >= log_min_messages);


	if (whereToSendOutput == DestRemote && elevel != COMMERROR)
	{


		if (ClientAuthInProgress)
			output_to_client = (elevel >= ERROR);
		else
			output_to_client = (elevel >= client_min_messages ||
								elevel == INFO);
	}


	if (elevel < ERROR && !output_to_server && !output_to_client)
		return false;


	if (recursion_depth++ > 0 && elevel >= ERROR)
	{


		MemoryContextReset(ErrorContext);


		if (in_error_recursion_trouble())
		{
			error_context_stack = NULL;
			debug_query_string = NULL;
		}
	}
	if (++errordata_stack_depth >= ERRORDATA_STACK_SIZE)
	{


		errordata_stack_depth = -1;
		ereport(PANIC, (errmsg_internal("ERRORDATA_STACK_SIZE exceeded")));
	}


	edata = &errordata[errordata_stack_depth];
	MemSet(edata, 0, sizeof(ErrorData));
	edata->elevel = elevel;
	edata->output_to_server = output_to_server;
	edata->output_to_client = output_to_client;
	edata->filename = filename;
	edata->lineno = lineno;
	edata->funcname = funcname;

	if (elevel >= ERROR)
		edata->sqlerrcode = ERRCODE_INTERNAL_ERROR;
	else if (elevel == WARNING)
		edata->sqlerrcode = ERRCODE_WARNING;
	else
		edata->sqlerrcode = ERRCODE_SUCCESSFUL_COMPLETION;

	edata->saved_errno = errno;

	recursion_depth--;
	return true;
}
