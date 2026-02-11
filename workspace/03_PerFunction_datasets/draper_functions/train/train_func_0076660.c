get_mining_stairs(Block *b)
{
    Block_var_table *bv;
    Array_subscript_info *assi;
    int i, stair, max, stair_max, min, stair_min;
    int mining_stair_type = MAX_SIZE;

    max = stair_max = -1;
    min = stair_min = 100;

    bv = b->def_var_list;
    for (i = 0; i < 2; i++) {
        switch (mining_stair_type) {
        case MAX_SIZE:
            for (assi = bv->array_sub_info;
                 assi != NULL;
                 assi = assi->next_array) {
                Array_table *apt
                    = search_array_table(b->module->array_head,
                                         assi->entry);
                if (max < byte2word(get_element_byte_size(apt->type, NULL)) * CORRECT_BYTE)
                    max = byte2word(get_element_byte_size(apt->type, NULL)) * CORRECT_BYTE;
            }
            if (stair_max < CACHE_LINE_SIZE / max)
                stair = stair_max = CACHE_LINE_SIZE / max;
            break;
        case MIN_SIZE:
            for (assi = bv->array_sub_info;
                 assi != NULL;
                 assi = assi->next_array) {
                Array_table *apt
                    = search_array_table(b->module->array_head,
                                         assi->entry);
                if (min > byte2word(get_element_byte_size(apt->type, NULL)) * CORRECT_BYTE)
                    min = byte2word(get_element_byte_size(apt->type, NULL)) * CORRECT_BYTE;
            }
            if (stair_min > CACHE_LINE_SIZE / min)
                stair = stair_min = CACHE_LINE_SIZE / min;
            break;
        case FIXED_VALUE:
        default:
            stair = MINING_STAIRS;
            break;
        }
        bv = b->use_var_list;
    }
    return stair;
}
