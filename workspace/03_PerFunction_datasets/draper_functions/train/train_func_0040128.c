e_rule_context_revert (ERuleContext *context,
                       const gchar *user)
{
	ERuleContextClass *class;

	g_return_val_if_fail (E_RULE_CONTEXT (context), 0);
	g_return_val_if_fail (user != NULL, 0);

	class = E_RULE_CONTEXT_GET_CLASS (context);
	g_return_val_if_fail (class->revert != NULL, 0);

	return class->revert (context, user);
}
