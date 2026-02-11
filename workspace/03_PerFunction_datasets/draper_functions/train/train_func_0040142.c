awt_sort_query_hits(const void *cl_item1, const void *cl_item2, void *cl_param) {
    awt_sort_query_hits_param *param = static_cast<awt_sort_query_hits_param*>(cl_param);

    GBDATA *gb_item1 = (GBDATA*)cl_item1;
    GBDATA *gb_item2 = (GBDATA*)cl_item2;

    struct adaqbsstruct    *cbs      = param->cbs;
    const ad_item_selector *selector = cbs->selector;

    int cmp = 0;

    for (int o = 0; o<MAX_CRITERIA && cmp == 0; o++) {
        AWT_QUERY_RESULT_ORDER criteria = param->order[o];

        switch (criteria) {
            case AWT_QUERY_SORT_NONE:
                o = MAX_CRITERIA;
                break;

            case AWT_QUERY_SORT_BY_1STFIELD_CONTENT: {
                char *field1 = GBT_read_as_string(gb_item1, param->first_key);
                char *field2 = GBT_read_as_string(gb_item2, param->first_key);

                cmp = strNULLcmp(field1, field2);

                free(field2);
                free(field1);
                break;
            }
            case AWT_QUERY_SORT_BY_NESTED_PID: {
                if (selector->parent_selector) {
                    GBDATA *gb_parent1 = selector->get_parent(gb_item1);
                    GBDATA *gb_parent2 = selector->get_parent(gb_item2);
                    char   *pid1       = AWT_get_item_id(cbs->gb_main, selector, gb_parent1);
                    char   *pid2       = AWT_get_item_id(cbs->gb_main, selector, gb_parent2);

                    cmp = strNULLcmp(pid1, pid2);

                    free(pid2);
                    free(pid1);
                }
                break;
            }
            case AWT_QUERY_SORT_BY_ID: {
                const char *id1 = GBT_read_char_pntr(gb_item1, selector->id_field);
                const char *id2 = GBT_read_char_pntr(gb_item2, selector->id_field);

                cmp = strcmp(id1, id2);
                break;
            }
            case AWT_QUERY_SORT_BY_MARKED:
                cmp = GB_read_flag(gb_item2)-GB_read_flag(gb_item1);
                break;

            case AWT_QUERY_SORT_BY_HIT_DESCRIPTION: {
                const char *id1   = GBT_read_char_pntr(gb_item1, selector->id_field);
                const char *id2   = GBT_read_char_pntr(gb_item2, selector->id_field);
                const char *info1 = reinterpret_cast<const char *>(GBS_read_hash(cbs->hit_description, id1));
                const char *info2 = reinterpret_cast<const char *>(GBS_read_hash(cbs->hit_description, id2));
                cmp = strNULLcmp(info1, info2);
                break;
            }
            case AWT_QUERY_SORT_REVERSE: {
                GBDATA *tmp = gb_item1;
                gb_item1    = gb_item2;
                gb_item2    = tmp;;
                break;
            }
        }
    }

    return cmp;
}
