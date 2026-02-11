free_slistener(slistener * l)
{
    network_close_listener(l->nlistener);
    oklog("UNLISTEN: #%d no longer listening on %s\n", l->oid, l->name);

    *(l->prev) = l->next;
    if (l->next)
	l->next->prev = l->prev;

    free_var(l->desc);
    free_str(l->name);

    myfree(l, M_NETWORK);
}
