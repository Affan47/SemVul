midgard_core_query_constraint_add_operator(MidgardCoreQueryConstraint *constraint, const gchar *op)
{
	if(!midgard_core_query_constraint_operator_is_valid(op))
		return FALSE;

	constraint->priv->condition_operator = g_strdup(op);

	return TRUE;
}
