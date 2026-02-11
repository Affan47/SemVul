test_do_destroy (GainsFixture *fixture, gconstpointer pData)
{
    Fixture *base = &(fixture->base);
    Split *base_split = g_list_nth_data (base->txn->splits, 1);
    QofBook *book = qof_instance_get_book (base->txn);
    TestSignal sig = test_signal_new (QOF_INSTANCE (base->txn),
                                      QOF_EVENT_DESTROY, NULL);
    g_object_add_weak_pointer (G_OBJECT (base->txn->splits->data),
                               (gpointer)&base_split);
    g_object_ref (base->txn);
    g_object_ref (fixture->gains_txn);

    base->func->do_destroy (base->txn);
    g_assert_cmpint (test_signal_return_hits (sig), ==, 1);
    g_assert (base->txn->description == NULL);
    g_assert_cmpint (GPOINTER_TO_INT(base->txn->num), ==, 1);
    g_assert (qof_instance_get_destroying (QOF_INSTANCE (fixture->gains_txn)));
    g_assert (base_split == NULL);

    test_signal_free (sig);
}
