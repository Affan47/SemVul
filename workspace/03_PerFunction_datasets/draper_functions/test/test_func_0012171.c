kui_should_continue_looking(struct kuictx *kctx,
        int *should_continue)
{
    std_list_iterator iter;
    struct kui_map_set *map_set;
    void *data;
    enum kui_tree_state map_state;

    if (!kctx)
        return -1;

    if (!should_continue)
        return -1;

    *should_continue = 0;


    for (iter = std_list_begin(kctx->kui_map_set_list);
            iter != std_list_end(kctx->kui_map_set_list);
            iter = std_list_next(iter)) {

        if (std_list_get_data(iter, &data) == -1)
            return -1;

        map_set = (struct kui_map_set *) data;

        if (kui_tree_get_state(map_set->ktree, &map_state) == -1)
            return -1;

        if (map_state == KUI_TREE_MATCHING)
            *should_continue = 1;
    }

    return 0;
}
