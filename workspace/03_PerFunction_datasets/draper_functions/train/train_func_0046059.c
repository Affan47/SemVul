walklist (List *list, int (*proc) (Node *, void *), void *closure)
{
    Node *head, *p;
    int err = 0;

#ifdef HAVE_PRINTF_PTR
    TRACE (TRACE_FLOW, "walklist ( list=%p, proc=%p, closure=%p )",
	   (void *)list, (void *)proc, (void *)closure);
#else
    TRACE (TRACE_FLOW, "walklist ( list=%lx, proc=%lx, closure=%lx )",
	   (unsigned long)list,(unsigned long) proc,
	   (unsigned long)closure);
#endif

    if (list == NULL)
	return 0;

    head = list->list;
    for (p = head->next; p != head; p = p->next)
	err += proc (p, closure);
    return err;
}
