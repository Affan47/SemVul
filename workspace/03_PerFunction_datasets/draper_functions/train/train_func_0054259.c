test_get_currency_denom (Fixture *fixture, gconstpointer pData)
{
    Transaction *txn = fixture->split->parent;
    const gint denom = gnc_commodity_get_fraction (fixture->curr);
    g_assert_cmpint (fixture->func->get_currency_denom (NULL), ==, 0);
    fixture->split->parent = NULL;
    g_assert_cmpint (fixture->func->get_currency_denom (fixture->split), ==, 100000);
    fixture->split->parent = txn;
    txn->common_currency = NULL;
    g_assert_cmpint (fixture->func->get_currency_denom (fixture->split), ==, 100000);
    txn->common_currency = fixture->curr;
    g_assert_cmpint (fixture->func->get_currency_denom (fixture->split), ==, denom);
}
