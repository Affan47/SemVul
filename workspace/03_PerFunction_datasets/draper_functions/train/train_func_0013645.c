get_append_kick_order(Kick_group *kickg,
                      IntSet syncs_mts,
                      Boolean post_mt_checkf)
{
    Kick_order *append;
    List *l;
    int position = 0;
    Kick_checkf_syncr *kcs = kickg->data;

    for (l = kcs->kick_order; l != NULL; l = l->next) {
        Kick_order *data = l->data;

        if (is_append_kick_order(data, syncs_mts, post_mt_checkf))
            return data;
        if (is_append_prev_kick_order(data, syncs_mts, post_mt_checkf)) {
            append = make_kick_order(syncs_mts, post_mt_checkf);
            kcs->kick_order = list_insert(kcs->kick_order,
                                          append, position);
            return append;
        }
        position++;
    }
    append = make_kick_order(syncs_mts, post_mt_checkf);
    kcs->kick_order = list_append(kcs->kick_order, append);
    return append;
}
