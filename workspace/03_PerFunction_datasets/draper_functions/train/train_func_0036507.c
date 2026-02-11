test_gnc_account_foreach_descendant (Fixture *fixture, gconstpointer pData)
{
    Account *root = gnc_account_get_root (fixture->acct);
    Account *begin = gnc_account_lookup_by_code (root, "4000");
    guint counter = 0;
    gnc_account_foreach_descendant (begin, thunk, &counter);
    g_assert_cmpint (counter, == , 13);
}
