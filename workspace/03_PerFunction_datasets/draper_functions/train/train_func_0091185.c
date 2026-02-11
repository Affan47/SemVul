snmpTargetParams_addSecName(struct targetParamTable_struct *entry,
                            char *cptr)
{
    size_t          len;
    if (cptr == NULL) {
        DEBUGMSGTL(("snmpTargetParamsEntry",
                    "ERROR snmpTargetParamsEntry: no security name in config string\n"));
        return (0);
    } else {
        len = strlen(cptr);
        entry->secName = (char *) malloc(len + 1);
        strncpy(entry->secName, cptr, len);
        entry->secName[len] = '\0';
    }
    return (1);
}
