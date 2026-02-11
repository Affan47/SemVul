client_search_transient(ObClient *self, ObClient *search)
{
    GSList *sit;

    for (sit = self->transients; sit; sit = g_slist_next(sit)) {
        if (sit->data == search)
            return search;
        if (client_search_transient(sit->data, search))
            return search;
    }
    return NULL;
}
