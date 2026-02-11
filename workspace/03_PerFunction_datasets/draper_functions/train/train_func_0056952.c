opal_hash_table_remove_value_uint64(opal_hash_table_t* ht, uint64_t key)
{
    opal_list_t* list = ht->ht_table + (key & ht->ht_mask);
    opal_uint64_hash_node_t *node;

#if OPAL_ENABLE_DEBUG
    if(ht->ht_table_size == 0) {
        opal_output(0, "opal_hash_table_remove_value_uint64:"
		   "opal_hash_table_init() has not been called");
        return OPAL_ERR_BAD_PARAM;
    }
#endif
    for(node =  (opal_uint64_hash_node_t*)opal_list_get_first(list);
        node != (opal_uint64_hash_node_t*)opal_list_get_end(list);
        node =  (opal_uint64_hash_node_t*)opal_list_get_next(node)) {
        if (node->hn_key == key) {
            opal_list_remove_item(list, (opal_list_item_t*)node);
            opal_list_append(&ht->ht_nodes, (opal_list_item_t*)node);
            ht->ht_size--;
            return OPAL_SUCCESS;
        }
    }
    return OPAL_ERR_NOT_FOUND;
}
