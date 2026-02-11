apreq_header_attribute(const char *hdr,
                           const char *name, const apr_size_t nlen,
                           const char **val, apr_size_t *vlen)
{
    const char *key, *v;


    while (*hdr == '=')
        ++hdr;

    while ((key = strchr(hdr, '=')) != NULL) {

        v = key + 1;
        --key;

        while (apr_isspace(*key) && key > hdr + nlen)
            --key;

        key -= nlen - 1;

        while (apr_isspace(*v))
            ++v;

        if (*v == '"') {
            ++v;
            *val = v;

        look_for_end_quote:
            switch (*v) {
            case '"':
                break;
            case 0:
                return APREQ_ERROR_BADSEQ;
            case '\\':
                if (v[1] != 0)
                    ++v;
            default:
                ++v;
                goto look_for_end_quote;
            }
        }
        else {
            *val = v;

        look_for_terminator:
            switch (*v) {
            case 0:
            case ' ':
            case ';':
            case ',':
            case '\t':
            case '\r':
            case '\n':
                break;
            default:
                ++v;
                goto look_for_terminator;
            }
        }

        if (key >= hdr && strncasecmp(key, name, nlen) == 0) {
            *vlen = v - *val;
            if (key == hdr || ! is_2616_token(key[-1]))
                return APR_SUCCESS;
        }
        hdr = v;
    }

    return APREQ_ERROR_NOATTR;
}
