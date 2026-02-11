plist_free_node(node_t* node)
{
    plist_data_t data = NULL;
    int index = node_detach(node->parent, node);
    data = plist_get_data(node);
    plist_free_data(data);
    node->data = NULL;

    node_iterator_t *ni = node_iterator_create(node->children);
    node_t *ch;
    while ((ch = node_iterator_next(ni))) {
        plist_free_node(ch);
    }
    node_iterator_destroy(ni);

    node_destroy(node);

    return index;
}
