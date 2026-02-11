define_custom_variable(struct config_generic * variable)
{
	const char *name = variable->name;
	const char **nameAddr = &name;
	const char *value;
	struct config_string *pHolder;
	GucContext	phcontext;
	struct config_generic **res;


	res = (struct config_generic **) bsearch((void *) &nameAddr,
											 (void *) guc_variables,
											 num_guc_variables,
											 sizeof(struct config_generic *),
											 guc_var_compare);
	if (res == NULL)
	{


		InitializeOneGUCOption(variable);
		add_guc_variable(variable, ERROR);
		return;
	}


	if (((*res)->flags & GUC_CUSTOM_PLACEHOLDER) == 0)
		ereport(ERROR,
				(errcode(ERRCODE_INTERNAL_ERROR),
				 errmsg("attempt to redefine parameter \"%s\"", name)));

	Assert((*res)->vartype == PGC_STRING);
	pHolder = (struct config_string *) (*res);


	InitializeOneGUCOption(variable);


	*res = variable;


	switch (pHolder->gen.source)
	{
		case PGC_S_DEFAULT:
		case PGC_S_DYNAMIC_DEFAULT:
		case PGC_S_ENV_VAR:
		case PGC_S_FILE:
		case PGC_S_ARGV:


			if (variable->context == PGC_POSTMASTER)
				phcontext = PGC_POSTMASTER;
			else
				phcontext = PGC_SIGHUP;
			break;

		case PGC_S_DATABASE:
		case PGC_S_USER:
		case PGC_S_DATABASE_USER:


			phcontext = PGC_SUSET;
			break;

		case PGC_S_CLIENT:
		case PGC_S_SESSION:
		default:


			phcontext = PGC_USERSET;
			break;
	}


	value = *pHolder->variable;

	if (value)
	{
		if (set_config_option(name, value,
							  phcontext, pHolder->gen.source,
							  GUC_ACTION_SET, true))
		{

			if (pHolder->gen.sourcefile)
				set_config_sourcefile(name, pHolder->gen.sourcefile,
									  pHolder->gen.sourceline);
		}
	}


	set_string_field(pHolder, pHolder->variable, NULL);
	set_string_field(pHolder, &pHolder->reset_val, NULL);

	free(pHolder);
}
