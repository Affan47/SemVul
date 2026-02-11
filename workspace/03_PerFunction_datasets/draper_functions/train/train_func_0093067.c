e_filter_rule_clone (EFilterRule *rule)
{
	EFilterRule *clone;

	g_return_val_if_fail (E_IS_FILTER_RULE (rule), NULL);

	clone = g_object_new (G_OBJECT_TYPE (rule), NULL);
	e_filter_rule_copy (clone, rule);

	return clone;
}
