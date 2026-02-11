add_string_reloption(bits32 kinds, char *name, char *desc, char *default_val,
					 validate_string_relopt validator)
{
	relopt_string *newoption;


	if (validator)
		(validator) (default_val);

	newoption = (relopt_string *) allocate_reloption(kinds, RELOPT_TYPE_STRING,
													 name, desc);
	newoption->validate_cb = validator;
	if (default_val)
	{
		newoption->default_val = MemoryContextStrdup(TopMemoryContext,
													 default_val);
		newoption->default_len = strlen(default_val);
		newoption->default_isnull = false;
	}
	else
	{
		newoption->default_val = "";
		newoption->default_len = 0;
		newoption->default_isnull = true;
	}

	add_reloption((relopt_gen *) newoption);
}
