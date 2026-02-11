do_destroy (Transaction *trans)
{
    SplitList *node;
    gboolean shutting_down = qof_book_shutting_down(qof_instance_get_book(trans));


    if (!shutting_down)
        destroy_gains (trans);


    if (!shutting_down && !qof_book_is_readonly(qof_instance_get_book(trans)))
        xaccTransWriteLog (trans, 'D');

    qof_event_gen (&trans->inst, QOF_EVENT_DESTROY, NULL);


    for (node = trans->splits; node; node = node->next)
    {
        Split *s = node->data;
        if (s && s->parent == trans)
        {
            xaccSplitDestroy(s);
        }
    }
    for (node = trans->splits; node; node = node->next)
    {
        Split *s = node->data;
        if (s && s->parent == trans)
        {
            xaccSplitCommitEdit(s);
        }
    }
    g_list_free (trans->splits);
    trans->splits = NULL;
    xaccFreeTransaction (trans);
}
