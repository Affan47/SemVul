xaccSplitRollbackEdit(Split *s)
{


    if (s->acc != s->orig_acc)
        s->acc = s->orig_acc;


    if (qof_instance_get_destroying(s) && s->parent)
    {
        GncEventData ed;
        qof_instance_set_destroying(s, FALSE);
        ed.node = s;
        ed.idx = -1;
        qof_event_gen(&s->parent->inst, GNC_EVENT_ITEM_ADDED, &ed);
    }


    xaccSplitSetParent(s, s->orig_parent);
}
