netsnmp_get_list_data(netsnmp_data_list *head, const char *name)
{
    if (!name)
        return NULL;
    for (; head; head = head->next)
        if (head->name && strcmp(head->name, name) == 0)
            break;
    if (head)
        return head->data;
    return NULL;
}
