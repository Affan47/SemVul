discard_stack_value(struct config_generic * gconf, union config_var_value * val)
{
	switch (gconf->vartype)
	{
		case PGC_BOOL:
		case PGC_INT:
		case PGC_REAL:
		case PGC_ENUM:

			break;
		case PGC_STRING:
			set_string_field((struct config_string *) gconf,
							 &(val->stringval),
							 NULL);
			break;
	}
}
