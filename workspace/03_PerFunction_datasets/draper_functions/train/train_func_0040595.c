GetConfigOptionByName(const char *name, const char **varname)
{
	struct config_generic *record;

	record = find_option(name, false, ERROR);
	if (record == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
			   errmsg("unrecognized configuration parameter \"%s\"", name)));
	if ((record->flags & GUC_SUPERUSER_ONLY) && !superuser())
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("must be superuser to examine \"%s\"", name)));

	if (varname)
		*varname = record->name;

	return _ShowOption(record, true);
}
