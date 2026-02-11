k5_unparse_name(krb5_context context, krb5_const_principal principal,
                int flags, char **name, unsigned int *size)
{
    char *q;
    krb5_int32 i;
    unsigned int totalsize = 0;
    char *default_realm = NULL;
    krb5_error_code ret = 0;

    if (!principal || !name)
        return KRB5_PARSE_MALFORMED;

    if (flags & KRB5_PRINCIPAL_UNPARSE_SHORT) {

        krb5_principal_data p;

        ret = krb5_get_default_realm(context, &default_realm);
        if (ret != 0)
            goto cleanup;

        p.realm = string2data(default_realm);

        if (krb5_realm_compare(context, &p, principal))
            flags |= KRB5_PRINCIPAL_UNPARSE_NO_REALM;
    }

    if ((flags & KRB5_PRINCIPAL_UNPARSE_NO_REALM) == 0) {
        totalsize += component_length_quoted(&principal->realm, flags);
        totalsize++;
    }

    for (i = 0; i < principal->length; i++) {
        totalsize += component_length_quoted(&principal->data[i], flags);
        totalsize++;
    }
    if (principal->length == 0)
        totalsize++;


    if (size) {
        if (*name && (*size < totalsize)) {
            *name = realloc(*name, totalsize);
        } else {
            *name = malloc(totalsize);
        }
        *size = totalsize;
    } else {
        *name = malloc(totalsize);
    }

    if (!*name) {
        ret = ENOMEM;
        goto cleanup;
    }

    q = *name;

    for (i = 0; i < principal->length; i++) {
        q += copy_component_quoting(q, &principal->data[i], flags);
        *q++ = COMPONENT_SEP;
    }

    if (i > 0)
        q--;
    if ((flags & KRB5_PRINCIPAL_UNPARSE_NO_REALM) == 0) {
        *q++ = REALM_SEP;
        q += copy_component_quoting(q, &principal->realm, flags);
    }
    *q++ = '\0';

cleanup:
    if (default_realm != NULL)
        krb5_free_default_realm(context, default_realm);

    return ret;
}
