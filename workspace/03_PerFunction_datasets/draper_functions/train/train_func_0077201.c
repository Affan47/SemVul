xmpp_buddy_create(XmppStream *stream, HybridBuddy *hybrid_buddy)
{
    XmppBuddy   *buddy;
    XmppAccount *account;
    gchar       *pos;

    g_return_val_if_fail(hybrid_buddy != NULL, NULL);

    account = stream->account;

    if (!account->buddies) {
        account->buddies = g_hash_table_new_full(g_str_hash, g_str_equal,
                NULL, (GDestroyNotify)xmpp_buddy_destroy);
    }

    if ((buddy = g_hash_table_lookup(account->buddies, hybrid_buddy->id))) {
        return buddy;
    }

    for (pos = hybrid_buddy->id; *pos; pos ++) {
        *pos = g_ascii_tolower(*pos);
    }

    buddy = g_new0(XmppBuddy, 1);
    buddy->jid = g_strdup(hybrid_buddy->id);
    buddy->buddy = hybrid_buddy;
    buddy->stream = stream;
    buddy->name = g_strdup(hybrid_buddy->name);

    xmpp_buddy_set_group_name(buddy, hybrid_buddy->parent->name);
    xmpp_buddy_set_photo(buddy, hybrid_blist_get_buddy_checksum(hybrid_buddy));

    g_hash_table_insert(account->buddies, buddy->jid, buddy);

    return buddy;
}
