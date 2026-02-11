classify_lm_var_info_list_for_one_block(Block *block,
                                        Scope_lm_var_info *outer_info)
{
    Scope_lm_var_info *p;
    int i;
    List *type_lm_var_info_list = NULL;

    List *list = list_sub_part(lm_var_info_list,
                               lm_var_info_cmp_block,
                               block);
    if (list == NULL)
        return NULL;
    lm_var_info_list = list_remove_sub_part(lm_var_info_list,
                                            list);

    for (i = 0; i < SHRINKED_TYPE_NUM; i++) {
        int m;
        List *li;
        Type_lm_var_info *q;

        symbol_type type = shrinked_type[i];

        m = (outer_info != NULL) ?
            scope_lm_var_info_get_max_lm_var_id(outer_info, type) : 0;
        li = list_sub_part(list, lm_var_info_cmp_type, &type);
        if (li == NULL && m == 0)
            continue;

        list = list_remove_sub_part(list, li);
        m = set_lm_var_id_to_list(li, m);

        if (max_lm_var_id[i] < m)
            max_lm_var_id[i] = m;

        q = type_lm_var_info_new(type, li, m);
        type_lm_var_info_list = list_append(type_lm_var_info_list, q);
    }

    p = scope_lm_var_info_new(block,
                              type_lm_var_info_list);
    scope_lm_var_info_list = list_append(scope_lm_var_info_list, p);

    return p;
}
