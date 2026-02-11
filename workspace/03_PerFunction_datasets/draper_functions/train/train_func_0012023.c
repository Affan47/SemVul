gnm_expr_entry_set_update_policy (GnmExprEntry *gee,
				       GnmUpdateType  policy)
{
	g_return_if_fail (IS_GNM_EXPR_ENTRY (gee));

	if (gee->update_policy == policy)
		return;
	gee->update_policy = policy;
	g_object_notify (G_OBJECT (gee), "update-policy");
}
