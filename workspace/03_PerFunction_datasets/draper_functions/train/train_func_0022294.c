apreq_parse_cookie_header(apr_pool_t *p,
                                                     apr_table_t *j,
                                                     const char *hdr)
{
    apreq_cookie_t *c;
    unsigned version;
    apr_status_t rv = APR_SUCCESS;

 parse_cookie_header:

    c = NULL;
    version = NETSCAPE;

    while (apr_isspace(*hdr))
        ++hdr;


    if (*hdr == '$' && strncasecmp(hdr, "$Version", 8) == 0) {

        version = RFC;
    skip_version_string:
        switch (*hdr++) {
        case 0:
            return rv;
        case ',':
            goto parse_cookie_header;
        case ';':
            break;
        default:
            goto skip_version_string;
        }
    }

    for (;;) {
        apr_status_t status;
        const char *name, *value;
        apr_size_t nlen, vlen;

        while (*hdr == ';' || apr_isspace(*hdr))
            ++hdr;

        switch (*hdr) {

        case 0:

            if (c != NULL) {
                ADD_COOKIE(j, c);
            }
            return rv;

        case ',':
            ++hdr;
            if (c != NULL) {
                ADD_COOKIE(j, c);
            }
            goto parse_cookie_header;

        case '$':
            ++hdr;
            if (c == NULL) {
                rv = APREQ_ERROR_BADCHAR;
                goto parse_cookie_error;
            }
            else if (version == NETSCAPE) {
                rv = APREQ_ERROR_MISMATCH;
            }

            status = get_pair(p, &hdr, &name, &nlen, &value, &vlen, 1);
            if (status != APR_SUCCESS) {
                rv = status;
                goto parse_cookie_error;
            }

            status = apreq_cookie_attr(p, c, name, nlen, value, vlen);

            switch (status) {

            case APR_ENOTIMPL:
                rv = APREQ_ERROR_BADATTR;


            case APR_SUCCESS:
                break;

            default:
                rv = status;
                goto parse_cookie_error;
            }

            break;

        default:
            if (c != NULL) {
                ADD_COOKIE(j, c);
            }

            status = get_pair(p, &hdr, &name, &nlen, &value, &vlen, 0);

            if (status != APR_SUCCESS) {
                c = NULL;
                rv = status;
                goto parse_cookie_error;
            }

            c = apreq_cookie_make(p, name, nlen, value, vlen);
            apreq_cookie_tainted_on(c);
            if (version != NETSCAPE)
                apreq_cookie_version_set(c, version);
        }
    }

 parse_cookie_error:

    switch (*hdr) {

    case 0:
        return rv;

    case ',':
    case ';':
        if (c != NULL)
            ADD_COOKIE(j, c);
        ++hdr;
        goto parse_cookie_header;

    default:
        ++hdr;
        goto parse_cookie_error;
    }


    return rv;
}
