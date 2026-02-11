real_event_destroy(struct event *evt)
{
    GSList *sl;
    for (sl = evt->subscribers; sl; sl = g_slist_next(sl))
        subscriber_destroy(sl->data);
}
