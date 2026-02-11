netsnmp_tdomain_support(const oid * in_oid,
                        size_t in_len,
                        const oid ** out_oid, size_t * out_len)
{
    netsnmp_tdomain *d = NULL;

    for (d = domain_list; d != NULL; d = d->next) {
        if (netsnmp_oid_equals(in_oid, in_len, d->name, d->name_length) == 0) {
            if (out_oid != NULL && out_len != NULL) {
                *out_oid = d->name;
                *out_len = d->name_length;
            }
            return 1;
        }
    }
    return 0;
}
