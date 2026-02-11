event_table_remove_all(struct event_table *t)
{
    g_assert(t != NULL);
    g_assert(t->events != NULL);

    hikset_foreach(t->events, clear_helper, NULL);
	hikset_clear(t->events);
}
