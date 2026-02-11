EmitWarningsOnPlaceholders(const char *className)
{
	int			classLen = strlen(className);
	int			i;

	for (i = 0; i < num_guc_variables; i++)
	{
		struct config_generic *var = guc_variables[i];

		if ((var->flags & GUC_CUSTOM_PLACEHOLDER) != 0 &&
			strncmp(className, var->name, classLen) == 0 &&
			var->name[classLen] == GUC_QUALIFIER_SEPARATOR)
		{
			ereport(WARNING,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("unrecognized configuration parameter \"%s\"",
							var->name)));
		}
	}
}
