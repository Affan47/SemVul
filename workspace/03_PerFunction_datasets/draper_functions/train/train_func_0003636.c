test_greet_authz_data(gss_name_t *name)
{
    OM_uint32 major, minor;
    gss_buffer_desc attr;
    gss_buffer_desc value;
    gss_name_t canon;

    major = gss_canonicalize_name(&minor, *name, &mech_krb5, &canon);
    check_gsserr("gss_canonicalize_name", major, minor);

    attr.value = "greet:greeting";
    attr.length = strlen((char *)attr.value);

    value.value = "Hello, acceptor world!";
    value.length = strlen((char *)value.value);

    major = gss_set_name_attribute(&minor, canon, 1, &attr, &value);
    if (major == GSS_S_UNAVAILABLE) {
        (void)gss_release_name(&minor, &canon);
        return;
    }
    check_gsserr("gss_set_name_attribute", major, minor);
    gss_release_name(&minor, name);
    *name = canon;
}
