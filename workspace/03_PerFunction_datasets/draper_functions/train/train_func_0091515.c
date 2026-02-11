gnm_style_cond_get_expr (GnmStyleCond const *cond, unsigned idx)
{
	g_return_val_if_fail (cond != NULL, NULL);
	g_return_val_if_fail (idx < G_N_ELEMENTS (cond->deps), NULL);

	return cond->deps[idx].texpr;
}
