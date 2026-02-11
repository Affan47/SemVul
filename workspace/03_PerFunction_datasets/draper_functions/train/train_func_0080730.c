e_cal_backend_sexp_match_object (ECalBackendSExp *sexp,
                                 const gchar *object,
                                 ETimezoneCache *cache)
{
	ECalComponent *comp;
	icalcomponent *icalcomp;
	gboolean retval;

	g_return_val_if_fail (E_IS_CAL_BACKEND_SEXP (sexp), FALSE);
	g_return_val_if_fail (object != NULL, FALSE);
	g_return_val_if_fail (E_IS_TIMEZONE_CACHE (cache), FALSE);

	icalcomp = icalcomponent_new_from_string ((gchar *) object);
	if (!icalcomp)
		return FALSE;

	comp = e_cal_component_new ();
	e_cal_component_set_icalcomponent (comp, icalcomp);

	retval = e_cal_backend_sexp_match_comp (sexp, comp, cache);

	g_object_unref (comp);

	return retval;
}
