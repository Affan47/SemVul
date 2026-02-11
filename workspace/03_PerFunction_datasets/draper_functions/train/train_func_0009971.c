snmpTargetAddrTable_create(void)
{
    struct targetAddrTable_struct *newEntry;

    newEntry = (struct targetAddrTable_struct *)
        malloc(sizeof(struct targetAddrTable_struct));

    if (newEntry) {
        newEntry->name = NULL;

        newEntry->tDomainLen = 0;
        newEntry->tAddress = NULL;

        newEntry->timeout = 1500;
        newEntry->retryCount = 3;

        newEntry->tagList = strdup("");
        newEntry->params = NULL;

        newEntry->storageType = SNMP_STORAGE_NONVOLATILE;
        newEntry->rowStatus = SNMP_ROW_NONEXISTENT;
        newEntry->sess = (netsnmp_session *) NULL;
        newEntry->next = NULL;
    }

    return newEntry;
}
