netsnmp_access_scopezone_entry_create(void)
{
    netsnmp_v6scopezone_entry *entry =
        SNMP_MALLOC_TYPEDEF(netsnmp_v6scopezone_entry);

    DEBUGMSGTL(("access:scopezone:entry", "create\n"));

    if(NULL == entry)
        return NULL;


    entry->oid_index.len = 1;
    entry->oid_index.oids =  &entry->ns_scopezone_index;

    return entry;
}
