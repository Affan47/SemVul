Scheduler_Seed_List_start_func(gpointer seed_data,
                                           gint seed_id, C4_Score score,
                                           gint start_query_pos,
                                           gint start_target_pos,
                                           STraceback_Cell *stcell){
    register Scheduler_Seed_List *seed_info_list = seed_data;
    register SDP_Seed *seed;
    g_assert(seed_info_list);
    g_assert(seed_info_list->seed_list);
    g_assert(seed_id < seed_info_list->sdp_pair->seed_list->len);
    seed = seed_info_list->sdp_pair->seed_list->pdata[seed_id];

    if(seed->max_start->score < score){
        seed->max_start->score = score;
        seed->max_start->query_pos = start_query_pos;
        seed->max_start->target_pos = start_target_pos;
        if(stcell)
            seed->max_start->cell = STraceback_Cell_share(stcell);
        else
            seed->max_start->cell = NULL;
        }
    return;
    }
