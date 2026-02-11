listRemoveFromTail(DLLIST  **phead,
                   DLLIST  **ptail)
{
DLLIST  *head, *tail;
void    *data;

    PROCNAME("listRemoveFromTail");

    if (!phead)
        return (void *)ERROR_PTR("&head not defined", procName, NULL);
    if ((head = *phead) == NULL)
        return (void *)ERROR_PTR("head not defined", procName, NULL);
    if (!ptail)
        return (void *)ERROR_PTR("&tail not defined", procName, NULL);
    if ((tail = *ptail) == NULL)
        tail = listFindTail(head);

    if (head->next == NULL) {
        *phead = NULL;
        *ptail = NULL;
    } else {
        tail->prev->next = NULL;
        *ptail = tail->prev;
    }

    data = tail->data;
    FREE(tail);
    return data;
}
