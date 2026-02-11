dns_list_prev(dns_list_t *list, dns_list_elem_t *elem)
{
    elem = elem->le_prev;
    if (elem == &list->l_head)
        return NULL;

    return elem;
}
