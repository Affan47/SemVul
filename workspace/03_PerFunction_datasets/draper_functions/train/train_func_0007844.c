parse_mteENotTable(const char *token, char *line)
{
    char   owner[MTE_STR1_LEN+1];
    char   ename[MTE_STR1_LEN+1];
    void  *vp;
    size_t len;
    struct mteEvent  *entry;

    DEBUGMSGTL(("disman:event:conf", "Parsing mteENotifyTable config...  "));


    memset( owner, 0, sizeof(owner));
    memset( ename, 0, sizeof(ename));
    len   = MTE_STR1_LEN; vp = owner;
    line  = read_config_read_data(ASN_OCTET_STR, line, &vp,  &len);
    len   = MTE_STR1_LEN; vp = ename;
    line  = read_config_read_data(ASN_OCTET_STR, line, &vp,  &len);
    entry = _find_mteEvent_entry( owner, ename );

    DEBUGMSG(("disman:event:conf", "(%s, %s) ", owner, ename));


    vp = entry->mteNotification;
    line  = read_config_read_data(ASN_OBJECT_ID, line, &vp,
                                 &entry->mteNotification_len);
    len   = MTE_STR1_LEN; vp = entry->mteNotifyOwner;
    line  = read_config_read_data(ASN_OCTET_STR, line, &vp,  &len);
    len   = MTE_STR1_LEN; vp = entry->mteNotifyObjects;
    line  = read_config_read_data(ASN_OCTET_STR, line, &vp,  &len);

    entry->mteEventActions |= MTE_EVENT_NOTIFICATION;
    entry->flags           |= MTE_EVENT_FLAG_VALID;

    DEBUGMSG(("disman:event:conf", "\n"));
}
