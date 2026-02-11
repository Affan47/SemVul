Bank (Ekiga::ServiceCore &_core): core(_core)
{
  GSList *accounts = gm_conf_get_string_list ("/apps/" PACKAGE_NAME "/protocols/accounts_list");
  GSList *accounts_iter = accounts;

  while (accounts_iter) {

    boost::shared_ptr<Account> account = boost::shared_ptr<Account> (new Account (core, (char *)accounts_iter->data));

    add_account (account);
    Ekiga::BankImpl<Account>::add_connection (account, account->trigger_saving.connect (boost::bind (&Opal::Bank::save, this)));
    Ekiga::BankImpl<Account>::add_connection (account, account->presence_received.connect (boost::ref (presence_received)));
    Ekiga::BankImpl<Account>::add_connection (account, account->status_received.connect (boost::ref (status_received)));
    accounts_iter = g_slist_next (accounts_iter);
  }

  g_slist_foreach (accounts, (GFunc) g_free, NULL);
  g_slist_free (accounts);
}
