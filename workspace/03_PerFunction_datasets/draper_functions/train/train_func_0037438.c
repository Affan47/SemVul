output_set_descr_header(char *desc_name)
{
	struct assignment *results;

	fprintf(yyout, "{ ECPGset_desc_header(__LINE__, %s, (int)(", desc_name);
	for (results = assignments; results != NULL; results = results->next)
	{
		if (results->value == ECPGd_count)
			ECPGnumeric_lvalue(results->variable);
		else
			mmerror(PARSE_ERROR, ET_WARNING, "descriptor header item \"%d\" does not exist", results->value);
	}

	drop_assignments();
	fprintf(yyout, "));\n");
	whenever_action(3);
}
