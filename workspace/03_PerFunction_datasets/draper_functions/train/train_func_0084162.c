print_ttilist(txn_test_iter **ttilist, size_t tticnt)
{
    while (tticnt > 0) {
        tticnt--;
        LDAPDebug2Args(LDAP_DEBUG_ANY,
                       "txn_test_threadmain: attr [%s] cnt [%lu]\n",
                       ttilist[tticnt]->attr, ttilist[tticnt]->cnt);
    }
}
