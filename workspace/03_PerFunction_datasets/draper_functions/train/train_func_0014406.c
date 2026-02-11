check_rowstatus_with_storagetype_transition(int oldValue, int newValue,
                                            int oldStorage)
{


    if ((RS_DESTROY == newValue) &&
        ((SNMP_STORAGE_PERMANENT == oldStorage) ||
         (SNMP_STORAGE_READONLY == oldStorage)))
        return SNMP_ERR_WRONGVALUE;

    return check_rowstatus_transition(oldValue, newValue);
}
