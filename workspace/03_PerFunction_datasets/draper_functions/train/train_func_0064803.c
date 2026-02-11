qof_query_run_cb(QofQueryCB* qcb, gpointer cb_arg)
{
    GList *node;

    (void)cb_arg;
    g_return_if_fail(qcb);

    for (node = qcb->query->books; node; node = node->next)
    {
        QofBook *book = node->data;
        QofBackend *be = book->backend;


        if (be)
        {
            gpointer compiled_query = g_hash_table_lookup (qcb->query->be_compiled,
                                      book);

            if (compiled_query && be->run_query)
            {
                (be->run_query) (be, compiled_query);
            }
        }


        qof_object_foreach (qcb->query->search_for, book,
                            (QofInstanceForeachCB) check_item_cb, qcb);
    }
}
