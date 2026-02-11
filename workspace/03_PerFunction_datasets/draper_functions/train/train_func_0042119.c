plist_get_data_val(plist_t node, char **val, uint64_t * length)
{
    plist_type type = plist_get_node_type(node);
    if (PLIST_DATA == type)
        plist_get_type_and_value(node, &type, (void *) val, length);
}
