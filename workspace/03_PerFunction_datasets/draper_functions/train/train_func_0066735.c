make_loop_prefetch_sub_list(Array_region_data *src,
                            int calc_offset)
{
    Prefetch_sub_data *ret;
    Sub_express *s = src->sub_express;

    ret = make_loop_prefetch_sub_data(src->sub_express,
                                      calc_offset);
    if (s->next_dim != NULL) {
        Prefetch_sub_data *tmp = ret;

        for (s = s->next_dim; s != NULL; s = s->next_dim) {
            tmp->next_dim = make_loop_prefetch_sub_data(s, 0);
            tmp = tmp->next_dim;
        }
    }
    return ret;
}
