set_stack_value(struct config_generic * gconf, union config_var_value * val)
{
	switch (gconf->vartype)
	{
		case PGC_BOOL:
			val->boolval =
				*((struct config_bool *) gconf)->variable;
			break;
		case PGC_INT:
			val->intval =
				*((struct config_int *) gconf)->variable;
			break;
		case PGC_REAL:
			val->realval =
				*((struct config_real *) gconf)->variable;
			break;
		case PGC_STRING:

			set_string_field((struct config_string *) gconf,
							 &(val->stringval),
							 *((struct config_string *) gconf)->variable);
			break;
	}
}
