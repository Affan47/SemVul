kadm5int_acl_check(kcontext, caller, opmask, principal, restrictions)
    krb5_context        kcontext;
    gss_name_t          caller;
    krb5_int32          opmask;
    krb5_principal      principal;
    restriction_t       **restrictions;
{
    krb5_boolean        retval;
    gss_buffer_desc     caller_buf;
    gss_OID             caller_oid;
    OM_uint32           emaj, emin;
    krb5_error_code     code;
    krb5_principal      caller_princ;

    if (GSS_ERROR(emaj = gss_display_name(&emin, caller, &caller_buf,
                                          &caller_oid)))
        return FALSE;

    code = krb5_parse_name(kcontext, (char *) caller_buf.value,
                           &caller_princ);

    gss_release_buffer(&emin, &caller_buf);

    if (code != 0)
        return FALSE;

    retval = kadm5int_acl_check_krb(kcontext, caller_princ,
                                    opmask, principal, restrictions);

    krb5_free_principal(kcontext, caller_princ);

    return retval;
}
