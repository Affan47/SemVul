release_netsnmp_request_group(netsnmp_index *g, void *v)
{
    netsnmp_request_group_item *tmp;
    netsnmp_request_group *group = (netsnmp_request_group *) g;

    if (!g)
        return;
    while (group->list) {
        tmp = group->list;
        group->list = tmp->next;
        free(tmp);
    }

    free(group);
}
