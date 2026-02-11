ctx_init(krb5_db2_context *dbc)
{
    krb5_error_code retval;
    char *polname = NULL, *plockname = NULL;

    retval = ctx_dbsuffix(dbc, SUFFIX_LOCK, &dbc->db_lf_name);
    if (retval)
        return retval;


    if ((dbc->db_lf_file = open(dbc->db_lf_name, O_RDWR, 0666)) < 0) {
        if ((dbc->db_lf_file = open(dbc->db_lf_name, O_RDONLY, 0666)) < 0) {
            retval = errno;
            goto cleanup;
        }
    }
    set_cloexec_fd(dbc->db_lf_file);
    dbc->db_inited++;

    retval = ctx_dbsuffix(dbc, SUFFIX_POLICY, &polname);
    if (retval)
        goto cleanup;
    retval = ctx_dbsuffix(dbc, SUFFIX_POLICY_LOCK, &plockname);
    if (retval)
        goto cleanup;
    retval = osa_adb_init_db(&dbc->policy_db, polname, plockname,
                             OSA_ADB_POLICY_DB_MAGIC);

cleanup:
    free(polname);
    free(plockname);
    if (retval)
        ctx_clear(dbc);
    return retval;
}
