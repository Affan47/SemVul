test_xaccTransClone (Fixture *fixture, gconstpointer pData)
{
    Timespec posted = gnc_dmy2timespec (12, 7, 2011);
    Timespec entered = gnc_dmy2timespec (14, 7, 2011);
    Transaction *new = NULL, *old = fixture->txn;
    QofBook *old_book = qof_instance_get_book (QOF_INSTANCE (old));
    GList *newnode, *oldnode;
    int foo, bar;

    old->date_posted = posted;
    old->date_entered = entered;
    new = xaccTransClone (old);

    g_assert_cmpstr (new->num, ==, old->num);
    g_assert_cmpstr (new->description, ==, old->description);

    g_assert_cmpint (xaccTransCountSplits (old), ==,
                     xaccTransCountSplits (new));

    xaccTransSortSplits (new);
    xaccTransSortSplits (old);

    oldnode = old->splits;
    for (newnode = new->splits; newnode && oldnode;
            newnode = g_list_next (newnode))
    {
        g_assert (xaccSplitEqual (newnode->data, oldnode->data,
                                  FALSE, FALSE, FALSE));
        oldnode = g_list_next (oldnode);
    }
    g_assert (newnode == NULL);
    g_assert (oldnode == NULL);
    g_assert (timespec_equal (&(new->date_posted), &posted));
    g_assert (timespec_equal (&(new->date_entered), &entered));
    g_assert (qof_instance_version_cmp (QOF_INSTANCE (new),
                                        QOF_INSTANCE (old)) == 0);
    g_assert_cmpint (qof_instance_get_version_check (new), ==,
                     qof_instance_get_version_check (old));
    g_assert (new->orig == NULL);
    g_assert (new->common_currency == fixture->curr);

    g_assert (qof_instance_get_book (QOF_INSTANCE (new)) == old_book);
    g_assert (kvp_frame_compare (old->inst.kvp_data, new->inst.kvp_data) == 0);

    test_destroy (new);
}
