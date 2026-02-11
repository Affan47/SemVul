make_prefetch_between_mt(Info_for_prefetch *info_p,
                         int sel_pe,
                         int use_mt,
                         int assigns,
                         int *assign,
                         real *TaskEndTime,
                         Array_def_use_table *cache_state)
{
    Array_def_use_table *du;
    int prefetch_mt, i;
    real *clock, max_clock;
    IntSet *some_mt, in_mt;
    Prefetch_array_data *ret;

    clock = get_array_def_clock(cache_state,
                                use_mt,
                                info_p->array_num,
                                info_p->task_num,
                                TaskEndTime,
                                info_p->du_chain);
    max_clock = get_max_clock(clock, info_p->array_num);

    prefetch_mt = decide_prefetch_mt_between_mt(info_p,
                                                use_mt,
                                                assigns,
                                                assign,
                                                TaskEndTime,
                                                max_clock);

    if (prefetch_mt == 0)
        return NULL;
    some_mt = (IntSet *)calloc(info_p->array_num + 1, sizeof (IntSet *));
    for (i = 0; i < info_p->array_num + 1; i++) {
        construct_IntSet(*(some_mt + i), info_p->task_num + 1);
        if (!(some_mt + i))
            fatal("No Room for IntSet. \n");
    }
    decide_some_prefetch_mt_between_mt(info_p,
                                       use_mt,
                                       assigns,
                                       assign,
                                       TaskEndTime,
                                       clock,
                                       cache_state,
                                       some_mt);
    construct_IntSet(in_mt, info_p->task_num + 1);
    collect_some_IntSet_to_one_IntSet(in_mt,
                                      some_mt,
                                      info_p->array_num);
    switch(mt_prefetch_type) {
    case 1:
        ret = make_prefetch_list_between_task(cache_state,
                                              info_p->mt_data[use_mt],
                                              info_p->mt_data[prefetch_mt]);
        break;
    case 2:
        for (du = cache_state; du != NULL; du = du->next)
            if (number_IntSet(some_mt[du->entry]) == 0)
                return NULL;
        ret = make_prefetch_list_between_task_in_some_mt_per_array(cache_state,
                                                                   info_p->mt_data[use_mt],
                                                                   info_p,
                                                                   some_mt);
        break;
    case 3:
        if (number_IntSet(in_mt) == 0)
            return NULL;
        ret = make_prefetch_list_between_task_in_some_mt(cache_state,
                                                         info_p->mt_data[use_mt],
                                                         info_p,
                                                         in_mt);
        break;
    default:
        break;
    }
    free(clock);
    for (i = 0; i < info_p->array_num + 1; i++)
        destruct_IntSet(*(some_mt + i));
    destruct_IntSet(in_mt);
    return ret;
}
