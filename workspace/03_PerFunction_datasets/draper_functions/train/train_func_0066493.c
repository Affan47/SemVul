cbf_reduce_list (cbf_compress_data *data,
                                    cbf_compress_node *list)
{
    cbf_compress_node *node, *next, *cnext;


    node = data->node + data->nextnode;

    data->nextnode++;


    node->child [0] = list;
    node->child [1] = list->next;
    node->count     = list->count + list->next->count;


    next = node->next = list->next->next;


    if (next == NULL)

        return node;

    if (node->count <= next->count)

        return node;


    cnext = next;

    while (cnext->next)

        if (node->count < cnext->count || node->count > cnext->next->count)

            cnext = cnext->next;

        else

            break;

    node->next  = cnext->next;
    cnext->next = node;

    return next;
}
