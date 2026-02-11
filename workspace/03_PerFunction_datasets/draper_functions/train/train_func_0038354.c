xmpp_buddy_add(HybridAccount *account, HybridGroup *group, const gchar *name,
               const gchar *alias, const gchar *tips)
{
    XmppStream *stream;

    stream = hybrid_account_get_protocol_data(account);

    if (xmpp_roster_add_item(stream, name, alias, group->name) != HYBRID_OK) {
        return FALSE;
    }

    return TRUE;
}
