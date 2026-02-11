show_one_credential(int authtracelevel,
                    krb5_context ctx, krb5_creds *cred)
{
    char *logname = "show_one_credential";
    krb5_error_code rc;
    char *name = NULL, *sname = NULL;
    char startts[BUFSIZ], endts[BUFSIZ], renewts[BUFSIZ];

    if ((rc = krb5_unparse_name(ctx, cred->client, &name))) {
        slapi_log_error(SLAPI_LOG_FATAL, logname,
                        "Could not get client name from credential: %d (%s)\n",
                        rc, error_message(rc));
        goto cleanup;
    }
    if ((rc = krb5_unparse_name(ctx, cred->server, &sname))) {
        slapi_log_error(SLAPI_LOG_FATAL, logname,
                        "Could not get server name from credential: %d (%s)\n",
                        rc, error_message(rc));
        goto cleanup;
    }
    if (!cred->times.starttime) {
        cred->times.starttime = cred->times.authtime;
    }
    krb5_timestamp_to_sfstring((krb5_timestamp)cred->times.starttime,
                               startts, sizeof(startts), NULL);
    krb5_timestamp_to_sfstring((krb5_timestamp)cred->times.endtime,
                               endts, sizeof(endts), NULL);
    krb5_timestamp_to_sfstring((krb5_timestamp)cred->times.renew_till,
                               renewts, sizeof(renewts), NULL);

    slapi_log_error(authtracelevel, logname,
                    "\tKerberos credential: client [%s] server [%s] "
                    "start time [%s] end time [%s] renew time [%s] "
                    "flags [0x%x]\n", name, sname, startts, endts,
                    renewts, (uint32_t)cred->ticket_flags);

cleanup:
    krb5_free_unparsed_name(ctx, name);
    krb5_free_unparsed_name(ctx, sname);

    return;
}
