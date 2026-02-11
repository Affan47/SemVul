parse(struct vtag *s, char const * const data, size_t bytes)
    {
    char const *p = data, *end = p + bytes;
    uint32_t len, to_do;
    int const min_vorbis_tag_size = 8;

    if (bytes < min_vorbis_tag_size)
        return VE_CROPPED;

    len = READINT(p);
    if (p + len + 4 > end)
        return VE_CROPPED;
    if (!(s->vendor_string = strndup(p, len)))
        return VE_ALLOCATION;
    p += len;

    to_do = READINT(p);

    while (to_do--) {
        if (p + 4 > end)
            return VE_CROPPED;

        len = READINT(p);
        if (p + len > end)
            return VE_CROPPED;

        switch (len) {
            case 0:
            case 1:
            case 2:
                return VE_SHORT_COMMENT;
            default:
                {
                char const * const sep = memchr(p + 1, '=', len - 1);
                if (!sep)
                    return VE_MISSING_SEPARATOR;
                if (sep + 1 - p == len)
                    return VE_MISSING_VALUE;
                if (!key_valid(p, sep - p))
                    return VE_INVALID_KEY;

                char *key = strlwr(strndup(p, sep - p));
                if (!key)
                    return VE_ALLOCATION;
                char *value = strndup(sep + 1, len - (sep + 1 - p));
                if (!value)
                    {
                    free(key);
                    return VE_ALLOCATION;
                    }

                insert_value(s->hash_table, key, value);
                }
            }
        p += len;
        }

    return VE_OK;
    }
