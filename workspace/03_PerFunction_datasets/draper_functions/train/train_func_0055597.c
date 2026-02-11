my_tzlookup(const gchar *tzid,
            gconstpointer ecalclient,
            GCancellable *cancellable,
            GError **error)
{
    icaltimezone *zone = NULL;
    GError *local_error = NULL;

    if (e_cal_client_get_timezone_sync((ECalClient *)ecalclient, tzid, &zone, cancellable, &local_error)) {
        return zone;
    } else if (local_error && local_error->domain == E_CAL_CLIENT_ERROR) {


        g_clear_error (&local_error);
    } else if (local_error) {
        g_propagate_error (error, local_error);
    }

    return NULL;
}
