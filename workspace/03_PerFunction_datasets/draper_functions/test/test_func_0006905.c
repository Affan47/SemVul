clear_cache(int action,
            u_char * var_val,
            u_char var_val_type,
            size_t var_val_len,
            u_char * statP, oid * name, size_t name_len)
{

    long            tmp = 0;

    if (var_val_type != ASN_INTEGER) {
        snmp_log(LOG_NOTICE, "Wrong type != int\n");
        return SNMP_ERR_WRONGTYPE;
    }
    tmp = *((long *) var_val);
    if (tmp == 1 && action == COMMIT) {
#ifdef NETSNMP_EXCACHETIME
        cachetime = 0;
#endif
    }
    return SNMP_ERR_NOERROR;
}
