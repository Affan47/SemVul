write_dict(GByteArray * bplist, GNode * node, GHashTable * ref_table, uint8_t dict_param_size)
{
    uint64_t idx1 = 0;
    uint64_t idx2 = 0;
    uint8_t *buff = NULL;

    GNode *cur = NULL;
    uint64_t i = 0;

    uint64_t size = g_node_n_children(node) / 2;
    uint8_t marker = BPLIST_DICT | (size < 15 ? size : 0xf);
    g_byte_array_append(bplist, &marker, sizeof(uint8_t));
    if (size >= 15)
    {
        GByteArray *int_buff = g_byte_array_new();
        write_int(int_buff, size);
        g_byte_array_append(bplist, int_buff->data, int_buff->len);
        g_byte_array_free(int_buff, TRUE);
    }

    buff = (uint8_t *) malloc(size * 2 * dict_param_size);

    for (i = 0, cur = node->children; cur && i < size; cur = cur->next->next, i++)
    {
        idx1 = *(uint64_t *) (g_hash_table_lookup(ref_table, cur));
#if G_BYTE_ORDER == G_BIG_ENDIAN
	idx1 = idx1 << ((sizeof(uint64_t) - dict_param_size) * 8);
#endif
        memcpy(buff + i * dict_param_size, &idx1, dict_param_size);
        byte_convert(buff + i * dict_param_size, dict_param_size);

        idx2 = *(uint64_t *) (g_hash_table_lookup(ref_table, cur->next));
#if G_BYTE_ORDER == G_BIG_ENDIAN
	idx2 = idx2 << ((sizeof(uint64_t) - dict_param_size) * 8);
#endif
        memcpy(buff + (i + size) * dict_param_size, &idx2, dict_param_size);
        byte_convert(buff + (i + size) * dict_param_size, dict_param_size);
    }


    g_byte_array_append(bplist, buff, size * 2 * dict_param_size);
    free(buff);

}
