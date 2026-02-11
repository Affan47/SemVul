conn_remove(conn c)
{
    if (!conn_list_any_p(c)) return NULL;

    c->next->prev = c->prev;
    c->prev->next = c->next;

    c->prev = c->next = c;
    return c;
}
