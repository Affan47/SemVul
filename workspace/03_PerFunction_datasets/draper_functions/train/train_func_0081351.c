list_ccache(krb5_ccache cache)
{
    krb5_error_code code;
    krb5_principal princ = NULL;
    char *princname = NULL, *ccname = NULL;
    int expired, status = 1;

    code = krb5_cc_get_principal(kcontext, cache, &princ);
    if (code)
        goto cleanup;
    code = krb5_unparse_name(kcontext, princ, &princname);
    if (code)
        goto cleanup;
    code = krb5_cc_get_full_name(kcontext, cache, &ccname);
    if (code)
        goto cleanup;

    status_only = 1;
    expired = do_ccache(cache);

    printf("%-30.30s %s", princname, ccname);
    if (expired)
        printf(" %s", _("(Expired)"));
    printf("\n");

    status = 0;
cleanup:
    krb5_free_principal(kcontext, princ);
    krb5_free_unparsed_name(kcontext, princname);
    krb5_free_string(kcontext, ccname);
    return status;
}
