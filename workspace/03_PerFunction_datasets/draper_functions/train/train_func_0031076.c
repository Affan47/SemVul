plist_array_insert_item(plist_t node, plist_t item, uint32_t n)
{
    if (node && PLIST_ARRAY == plist_get_node_type(node))
    {
        node_insert(node, n, item);
    }
    return;
}
