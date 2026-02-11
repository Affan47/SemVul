ctx_dbsuffix(krb5_db2_context *dbc, const char *sfx, char **out)
{
    char *result;
    const char *tilde;

    *out = NULL;
    tilde = dbc->tempdb ? "~" : "";
    if (asprintf(&result, "%s%s%s", dbc->db_name, tilde, sfx) < 0)
        return ENOMEM;
    *out = result;
    return 0;
}
