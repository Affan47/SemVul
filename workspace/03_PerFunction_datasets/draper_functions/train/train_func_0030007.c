sprint_realloc_gauge(u_char ** buf, size_t * buf_len, size_t * out_len,
                     int allow_realloc,
                     const netsnmp_variable_list * var,
                     const struct enum_list *enums,
                     const char *hint, const char *units)
{
    char            tmp[32];

    if ((var->type != ASN_GAUGE) &&
        (!netsnmp_ds_get_boolean(NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_QUICKE_PRINT))) {
        u_char          str[] =
            "Wrong Type (should be Gauge32 or Unsigned32): ";
        if (snmp_strcat(buf, buf_len, out_len, allow_realloc, str)) {
            return sprint_realloc_by_type(buf, buf_len, out_len,
                                          allow_realloc, var, NULL, NULL,
                                          NULL);
        } else {
            return 0;
        }
    }

    if (!netsnmp_ds_get_boolean(NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_QUICK_PRINT)) {
        u_char          str[] = "Gauge32: ";
        if (!snmp_strcat(buf, buf_len, out_len, allow_realloc, str)) {
            return 0;
        }
    }
    if (hint) {
        if (!sprint_realloc_hinted_integer(buf, buf_len, out_len,
                                           allow_realloc,
                                           *var->val.integer, 'u', hint,
                                           units)) {
            return 0;
        }
    } else {
        sprintf(tmp, "%u", (unsigned int)(*var->val.integer & 0xffffffff));
        if (!snmp_strcat
            (buf, buf_len, out_len, allow_realloc, (const u_char *) tmp)) {
            return 0;
        }
    }
    if (units) {
        return (snmp_strcat
                (buf, buf_len, out_len, allow_realloc,
                 (const u_char *) " ")
                && snmp_strcat(buf, buf_len, out_len, allow_realloc,
                               (const u_char *) units));
    }
    return 1;
}
