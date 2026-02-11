k5_try_realm_txt_rr(krb5_context context, const char *prefix, const char *name,
                    char **realm)
{
    krb5_error_code retval = KRB5_ERR_HOST_REALM_UNKNOWN;
    const unsigned char *p, *base;
    char host[MAXDNAME];
    int ret, rdlen, len;
    struct krb5int_dns_state *ds = NULL;
    struct k5buf buf;


    k5_buf_init_fixed(&buf, host, sizeof(host));
    if (name == NULL || name[0] == '\0') {
        k5_buf_add(&buf, prefix);
    } else {
        k5_buf_add_fmt(&buf, "%s.%s", prefix, name);


        len = k5_buf_len(&buf);
        if (len > 0 && host[len - 1] != '.')
            k5_buf_add(&buf, ".");
    }
    if (k5_buf_data(&buf) == NULL)
        return KRB5_ERR_HOST_REALM_UNKNOWN;
    ret = krb5int_dns_init(&ds, host, C_IN, T_TXT);
    if (ret < 0) {
        TRACE_TXT_LOOKUP_NOTFOUND(context, host);
        goto errout;
    }

    ret = krb5int_dns_nextans(ds, &base, &rdlen);
    if (ret < 0 || base == NULL)
        goto errout;

    p = base;
    if (!INCR_OK(base, rdlen, p, 1))
        goto errout;
    len = *p++;
    *realm = malloc((size_t)len + 1);
    if (*realm == NULL) {
        retval = ENOMEM;
        goto errout;
    }
    strncpy(*realm, (const char *)p, (size_t)len);
    (*realm)[len] = '\0';

    if ( (*realm)[len-1] == '.' )
        (*realm)[len-1] = '\0';
    retval = 0;
    TRACE_TXT_LOOKUP_SUCCESS(context, host, *realm);

errout:
    if (ds != NULL) {
        krb5int_dns_fini(ds);
        ds = NULL;
    }
    return retval;
}
