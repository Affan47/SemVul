event_table_add_event(struct event_table *t, struct event *evt)
{
    g_assert(t != NULL);
    g_assert(evt != NULL);

    g_assert(t->events != NULL);
    g_assert(!hikset_contains(t->events, evt->name));

    hikset_insert_key(t->events, &evt->name);
}
