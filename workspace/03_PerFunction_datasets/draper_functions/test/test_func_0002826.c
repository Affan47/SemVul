gnm_expr_entry_enable_tips (GnmExprEntry *gee)
{
	g_return_if_fail (gee != NULL);
	gee->tooltip.enabled = TRUE;
}
