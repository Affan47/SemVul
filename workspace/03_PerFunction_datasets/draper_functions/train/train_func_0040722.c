fdevent_call_fdfunc(fdevent* fde)
{
    unsigned events = fde->events;
    fde->events = 0;
    if(!(fde->state & FDE_PENDING)) return;
    fde->state &= (~FDE_PENDING);
    dump_fde(fde, "callback");
    fde->func(fde->fd, events, fde->arg);
}
