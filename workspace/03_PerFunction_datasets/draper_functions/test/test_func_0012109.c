output_set_descr(char *desc_name, char *index)
{
	struct assignment *results;

	fprintf(yyout, "{ ECPGset_desc(__LINE__, %s, %s,", desc_name, index);
	for (results = assignments; results != NULL; results = results->next)
	{
		const struct variable *v = find_variable(results->variable);

		switch (results->value)
		{
			case ECPGd_cardinality:
			case ECPGd_di_code:
			case ECPGd_di_precision:
			case ECPGd_precision:
			case ECPGd_scale:
				mmfatal(PARSE_ERROR, "descriptor item \"%s\" is not implemented",
						descriptor_item_name(results->value));
				break;

			case ECPGd_key_member:
			case ECPGd_name:
			case ECPGd_nullable:
			case ECPGd_octet:
			case ECPGd_ret_length:
			case ECPGd_ret_octet:
				mmfatal(PARSE_ERROR, "descriptor item \"%s\" cannot be set",
						descriptor_item_name(results->value));
				break;

			case ECPGd_data:
			case ECPGd_indicator:
			case ECPGd_length:
			case ECPGd_type:
				{
					char *str_zero = mm_strdup("0");
					fprintf(yyout, "%s,", get_dtype(results->value));
					ECPGdump_a_type(yyout, v->name, v->type, v->brace_level, NULL, NULL, -1, NULL, NULL, str_zero, NULL, NULL);
					free(str_zero);
				}
				break;

			default:
				;
		}
	}
	drop_assignments();
	fputs("ECPGd_EODT);\n", yyout);

	whenever_action(2 | 1);
}
