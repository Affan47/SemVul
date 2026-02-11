sprint_realloc_timeticks(u_char ** buf, size_t * buf_len, size_t * out_len,
                         int allow_realloc,
                         const netsnmp_variable_list * var,
                         const struct enum_list *enums,
                         const char *hint, const char *units)
{
    char            timebuf[40];

    if ((var->type != ASN_TIMETICKS) &&
        (!netsnmp_ds_get_boolean(NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_QUICKE_PRINT))) {
        u_char          str[] = "Wrong Type (should be Timeticks): ";
        if (snmp_strcat(buf, buf_len, out_len, allow_realloc, str)) {
            return sprint_realloc_by_type(buf, buf_len, out_len,
                                          allow_realloc, var, NULL, NULL,
                                          NULL);
        } else {
            return 0;
        }
    }

    if (netsnmp_ds_get_boolean(NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_NUMERIC_TIMETICKS)) {
        char            str[32];
        sprintf(str, "%lu", *(u_long *) var->val.integer);
        if (!snmp_strcat
            (buf, buf_len, out_len, allow_realloc, (const u_char *) str)) {
            return 0;
        }
        return 1;
    }
    if (!netsnmp_ds_get_boolean(NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_QUICK_PRINT)) {
        char            str[32];
        sprintf(str, "Timeticks: (%lu) ", *(u_long *) var->val.integer);
        if (!snmp_strcat
            (buf, buf_len, out_len, allow_realloc, (const u_char *) str)) {
            return 0;
        }
    }
    uptimeString(*(u_long *) (var->val.integer), timebuf, sizeof(timebuf));
    if (!snmp_strcat
        (buf, buf_len, out_len, allow_realloc, (const u_char *) timebuf)) {
        return 0;
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
