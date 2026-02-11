SDP_Pair_find_end_points(SDP_Pair *sdp_pair){
    register Scheduler_Pair *spair;
    register Scheduler_Seed_List *seed_info_list = NULL;
    register Scheduler_Seed_Boundary *seed_info_boundary = NULL;
    if(sdp_pair->boundary){
        g_assert(sdp_pair->boundary->row_list->len);
        seed_info_boundary = Scheduler_Seed_Boundary_create(sdp_pair->boundary,
                                                            sdp_pair);
        spair = Scheduler_Pair_create(sdp_pair->sdp->find_ends_scheduler,
                          sdp_pair->fwd_straceback,
                          sdp_pair->comparison->query->len,
                          sdp_pair->comparison->target->len,
                          sdp_pair->subopt,
                          sdp_pair->boundary, -1, seed_info_boundary,
                          sdp_pair->user_data);
    } else {
        seed_info_list = Scheduler_Seed_List_create(sdp_pair, TRUE);
        spair = Scheduler_Pair_create(sdp_pair->sdp->find_ends_scheduler,
                          sdp_pair->fwd_straceback,
                          sdp_pair->comparison->query->len,
                          sdp_pair->comparison->target->len,
                          sdp_pair->subopt,
                          sdp_pair->boundary, -1, seed_info_list,
                          sdp_pair->user_data);
        }
    Scheduler_Pair_calculate(spair);
    Scheduler_Pair_destroy(spair);
    if(sdp_pair->boundary){
        g_assert(seed_info_boundary);
        Scheduler_Seed_Boundary_destroy(seed_info_boundary);
    } else {
        g_assert(seed_info_list);
        Scheduler_Seed_List_destroy(seed_info_list);
        }
    return;
    }
