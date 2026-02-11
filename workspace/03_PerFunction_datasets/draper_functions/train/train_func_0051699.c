e_cal_get_default_object (ECal *ecal,
                          icalcomponent **icalcomp,
                          GError **error)
{
	g_return_val_if_fail (E_IS_CAL (ecal), FALSE);
	g_return_val_if_fail (icalcomp != NULL, FALSE);

	return e_cal_client_get_default_object_sync (
		ecal->priv->client, icalcomp, NULL, error);
}
