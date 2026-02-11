write_vacmViewSpinLock(int action,
                       u_char * var_val,
                       u_char var_val_type,
                       size_t var_val_len,
                       u_char * statP, oid * name, size_t name_len)
{
    static long     long_ret;

    if (action == RESERVE1) {
        if (var_val_type != ASN_INTEGER) {
            DEBUGMSGTL(("mibII/vacm_vars",
                        "write to vacmViewSpinLock not ASN_INTEGER\n"));
            return SNMP_ERR_WRONGTYPE;
        }
        if (var_val_len != sizeof(long_ret)) {
            DEBUGMSGTL(("mibII/vacm_vars",
                        "write to vacmViewSpinLock: bad length\n"));
            return SNMP_ERR_WRONGLENGTH;
        }
        long_ret = *((long *) var_val);
        if (long_ret != (long) vacmViewSpinLock) {
            return SNMP_ERR_INCONSISTENTVALUE;
        }
    } else if (action == COMMIT) {
        if (vacmViewSpinLock == 2147483647) {
            vacmViewSpinLock = 0;
        } else {
            vacmViewSpinLock++;
        }
    }
    return SNMP_ERR_NOERROR;
}
