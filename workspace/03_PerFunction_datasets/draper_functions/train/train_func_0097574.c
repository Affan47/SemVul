e_cal_discard_alarm (ECal *ecal,
                     ECalComponent *comp,
                     const gchar *auid,
                     GError **error)
{
	g_return_val_if_fail (E_IS_CAL (ecal), FALSE);
	g_return_val_if_fail (E_IS_CAL_COMPONENT (comp), FALSE);
	g_return_val_if_fail (auid != NULL, FALSE);

	g_set_error (
		error, E_CALENDAR_ERROR,
		E_CALENDAR_STATUS_NOT_SUPPORTED,
		_("Not supported"));

	return FALSE;
}
