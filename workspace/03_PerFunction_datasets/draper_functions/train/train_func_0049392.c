write_usmUserStorageType(int action,
                         u_char * var_val,
                         u_char var_val_type,
                         size_t var_val_len,
                         u_char * statP, oid * name, size_t name_len)
{
    long            long_ret = *((long *) var_val);
    static long     oldValue;
    struct usmUser *uptr;
    static int      resetOnFail;

    if (action == RESERVE1) {
        resetOnFail = 0;
        if (var_val_type != ASN_INTEGER) {
            DEBUGMSGTL(("usmUser",
                        "write to usmUserStorageType not ASN_INTEGER\n"));
            return SNMP_ERR_WRONGTYPE;
        }
        if (var_val_len != sizeof(long)) {
            DEBUGMSGTL(("usmUser",
                        "write to usmUserStorageType: bad length\n"));
            return SNMP_ERR_WRONGLENGTH;
        }
        if (long_ret < 1 || long_ret > 5) {
            return SNMP_ERR_WRONGVALUE;
        }
    } else if (action == RESERVE2) {
        if ((uptr = usm_parse_user(name, name_len)) == NULL) {
            return SNMP_ERR_INCONSISTENTNAME;
        }
        if ((long_ret == ST_VOLATILE || long_ret == ST_NONVOLATILE) &&
            (uptr->userStorageType == ST_VOLATILE ||
             uptr->userStorageType == ST_NONVOLATILE)) {
            oldValue = uptr->userStorageType;
            uptr->userStorageType = long_ret;
            resetOnFail = 1;
        } else {


            DEBUGMSGTL(("usmUser",
                        "long_ret %ld uptr->st %d uptr->status %d\n",
                        long_ret, uptr->userStorageType,
                        uptr->userStatus));

            if (long_ret == ST_READONLY &&
                uptr->userStorageType != ST_READONLY &&
                (uptr->userStatus == RS_ACTIVE ||
                 uptr->userStatus == RS_NOTINSERVICE)) {
                return SNMP_ERR_WRONGVALUE;
            } else if (long_ret == ST_READONLY &&
                       (snmp_oid_compare
                        (uptr->privProtocol, uptr->privProtocolLen,
                         usmNoPrivProtocol,
                         sizeof(usmNoPrivProtocol) / sizeof(oid)) != 0
                        || snmp_oid_compare(uptr->authProtocol,
                                            uptr->authProtocolLen,
                                            usmNoAuthProtocol,
                                            sizeof(usmNoAuthProtocol) /
                                            sizeof(oid)) != 0)) {
                return SNMP_ERR_INCONSISTENTVALUE;
            } else {
                return SNMP_ERR_WRONGVALUE;
            }
        }
    } else if (action == UNDO || action == FREE) {
        if ((uptr = usm_parse_user(name, name_len)) != NULL && resetOnFail) {
            uptr->userStorageType = oldValue;
        }
    }
    return SNMP_ERR_NOERROR;
}
