dump_realloc_oid_to_string(const oid * objid, size_t objidlen,
                           u_char ** buf, size_t * buf_len,
                           size_t * out_len, int allow_realloc,
                           char quotechar)
{
    if (buf) {
        int             i, alen;

        for (i = 0, alen = 0; i < (int) objidlen; i++) {
            oid             tst = objid[i];
            if ((tst > 254) || (!isprint(tst))) {
                tst = (oid) '.';
            }

            if (alen == 0) {
                if (netsnmp_ds_get_boolean(NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_ESCAPE_QUOTES)) {
                    while ((*out_len + 2) >= *buf_len) {
                        if (!(allow_realloc && snmp_realloc(buf, buf_len))) {
                            return 0;
                        }
                    }
                    *(*buf + *out_len) = '\\';
                    (*out_len)++;
                }
                while ((*out_len + 2) >= *buf_len) {
                    if (!(allow_realloc && snmp_realloc(buf, buf_len))) {
                        return 0;
                    }
                }
                *(*buf + *out_len) = quotechar;
                (*out_len)++;
            }

            while ((*out_len + 2) >= *buf_len) {
                if (!(allow_realloc && snmp_realloc(buf, buf_len))) {
                    return 0;
                }
            }
            *(*buf + *out_len) = (char) tst;
            (*out_len)++;
            alen++;
        }

        if (alen) {
            if (netsnmp_ds_get_boolean(NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_ESCAPE_QUOTES)) {
                while ((*out_len + 2) >= *buf_len) {
                    if (!(allow_realloc && snmp_realloc(buf, buf_len))) {
                        return 0;
                    }
                }
                *(*buf + *out_len) = '\\';
                (*out_len)++;
            }
            while ((*out_len + 2) >= *buf_len) {
                if (!(allow_realloc && snmp_realloc(buf, buf_len))) {
                    return 0;
                }
            }
            *(*buf + *out_len) = quotechar;
            (*out_len)++;
        }

        *(*buf + *out_len) = '\0';
    }

    return 1;
}
