upstart_job_exists(const char *name)
{
    char *path = NULL;
    GError *error = NULL;
    gboolean pass = FALSE;

    if (upstart_init() == FALSE) {
        return FALSE;
    }

    pass = upstart_job_by_name(upstart_proxy, name, &path, NULL, &error);

    if (error) {
        crm_trace("Call to ListUnits failed: %s", error->message);
        g_error_free(error);
        pass = FALSE;

    } else if (pass) {
        crm_trace("Got %s", path);
    }

    return pass;
}
