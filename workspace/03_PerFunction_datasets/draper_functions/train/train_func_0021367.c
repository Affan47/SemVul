xmpp_account_create(HybridAccount *account, const gchar *username,
                    const gchar *password, const gchar *to)
{
    XmppAccount *ac;

    g_return_val_if_fail(account != NULL, NULL);
    g_return_val_if_fail(username != NULL, NULL);
    g_return_val_if_fail(password != NULL, NULL);
    g_return_val_if_fail(to != NULL, NULL);

    ac = g_new0(XmppAccount, 1);

    ac->account  = account;
    ac->username = g_strdup(username);
    ac->password = g_strdup(password);
    ac->to       = g_strdup(to);

    return ac;
}
