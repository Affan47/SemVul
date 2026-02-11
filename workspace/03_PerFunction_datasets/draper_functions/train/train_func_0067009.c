find_node_by_name(const gchar * name)
{
    GList *ptr;

    for (ptr = get_list_head(); ptr != NULL; ptr = ptr->next)
        if (ptr->data == name)
            return ptr;

    return NULL;
}
