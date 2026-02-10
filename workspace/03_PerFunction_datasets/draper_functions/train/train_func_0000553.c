snmpTargetAddr_addTagList(struct targetAddrTable_struct *entry, char *cptr)
{
    if (cptr == NULL) {
        DEBUGMSGTL(("snmpTargetAddrEntry",
                    "ERROR snmpTargetAddrEntry: no tag list in config string\n"));
        return (0);
    } else {
        size_t len = strlen(cptr);


        if (len > 255) {
            DEBUGMSGTL(("snmpTargetAddrEntry",
                        "ERROR snmpTargetAddrEntry: tag list out of range in config string\n"));
            return (0);
        }
        SNMP_FREE(entry->tagList);
        entry->tagList = (char *) malloc(len + 1);
        strncpy(entry->tagList, cptr, len);
        entry->tagList[len] = '\0';
    }
    return (1);
}
