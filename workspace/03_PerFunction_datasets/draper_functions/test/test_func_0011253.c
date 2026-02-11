stktable_compatible_sample(struct sample_expr *expr, unsigned long table_type)
{
	int out_type;

	if (table_type >= STKTABLE_TYPES)
		return 0;

	out_type = smp_expr_output_type(expr);
	if (!sample_to_key[out_type][table_type])
		return 0;

	return 1;
}
