exchange_bus_state(List *a, List *b)
{
    List *tmp;

    tmp = a->next;
    a->next = b->next;
    if (a->next != NULL)
        a->next->prev = a;
    b->next = tmp;
    if (b->next != NULL)
        b->next->prev = b;
}
