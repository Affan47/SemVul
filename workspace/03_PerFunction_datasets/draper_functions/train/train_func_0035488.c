gkm_sexp_key_set_base (GkmSexpKey *self, GkmSexp *sexp)
{
	g_return_if_fail (GKM_IS_SEXP_KEY (self));
	if (sexp)
		gkm_sexp_ref (sexp);
	if (self->pv->base_sexp)
		gkm_sexp_unref (self->pv->base_sexp);
	self->pv->base_sexp = sexp;
	g_object_notify (G_OBJECT (self), "base-sexp");
	g_object_notify (G_OBJECT (self), "algorithm");
}
