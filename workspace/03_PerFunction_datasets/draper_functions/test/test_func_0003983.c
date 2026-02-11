e_cal_backend_sexp_match_comp (ECalBackendSExp *sexp,
                               ECalComponent *comp,
                               ETimezoneCache *cache)
{
	ESExpResult *r;
	gboolean retval;

	g_return_val_if_fail (E_IS_CAL_BACKEND_SEXP (sexp), FALSE);
	g_return_val_if_fail (E_IS_CAL_COMPONENT (comp), FALSE);
	g_return_val_if_fail (E_IS_TIMEZONE_CACHE (cache), FALSE);

	sexp->priv->search_context->comp = g_object_ref (comp);
	sexp->priv->search_context->cache = g_object_ref (cache);

	r = e_sexp_eval (sexp->priv->search_sexp);

	retval = (r && r->type == ESEXP_RES_BOOL && r->value.boolean);

	g_object_unref (sexp->priv->search_context->comp);
	g_object_unref (sexp->priv->search_context->cache);

	e_sexp_result_free (sexp->priv->search_sexp, r);

	return retval;
}
