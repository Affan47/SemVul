gda_sql_operation_copy (GdaSqlOperation *operation)
{
	GdaSqlOperation *copy;
	GSList *list;

	if (!operation) return NULL;

	copy = gda_sql_operation_new (NULL);
	copy->operator_type = operation->operator_type;

	for (list = operation->operands; list; list = list->next) {
		copy->operands = g_slist_prepend (copy->operands,
						  gda_sql_expr_copy ((GdaSqlExpr*) list->data));
		gda_sql_any_part_set_parent (copy->operands->data, copy);
	}
	copy->operands = g_slist_reverse (copy->operands);

	return copy;
}
