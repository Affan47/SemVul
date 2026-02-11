HPair_find_candidate_hsp_pairs(HPair *hpair,
                                           Heuristic_Pair *pair,
                                           gint *edge_total){
    register gint src_portal_id = pair->src->portal->id,
                  dst_portal_id = pair->dst->portal->id;
    register HSPset
        *src_hsp_set = hpair->portal_data_list->pdata[src_portal_id],
        *dst_hsp_set = hpair->portal_data_list->pdata[dst_portal_id];
    register C4_Portal
        *src_portal = hpair->heuristic->model->portal_list->pdata
                                                  [src_portal_id],
        *dst_portal = hpair->heuristic->model->portal_list->pdata
                                                  [dst_portal_id];
    register HSP *src, *dst;
    register gint i;
    register RangeTree *rangetree = RangeTree_create();
    register HSP *max_dst_cobs_hsp;
    g_assert(src_portal == pair->src->portal);
    g_assert(dst_portal == pair->dst->portal);
    gint max_query_join_range, max_target_join_range;
    HPair_RangeTree_Report_Data hrtrd;
    g_assert(src_hsp_set);
    g_assert(dst_hsp_set);
    max_dst_cobs_hsp = dst_hsp_set->hsp_list->pdata[0];
    hrtrd.hpair = hpair;
    hrtrd.pair = pair;
    hrtrd.src_portal = src_portal;
    hrtrd.dst_portal = dst_portal;
    hrtrd.dst_hsp_set = dst_hsp_set;
    hrtrd.edge_total = edge_total;
    Heuristic_Pair_get_max_range(pair, &max_query_join_range,
                                       &max_target_join_range);

    for(i = 0; i < dst_hsp_set->hsp_list->len; i++){
        dst = dst_hsp_set->hsp_list->pdata[i];
        RangeTree_add(rangetree,
                      HSP_query_cobs(dst), HSP_target_cobs(dst),
                      GINT_TO_POINTER(i));
        if(max_dst_cobs_hsp->cobs < dst->cobs)
           max_dst_cobs_hsp = dst;
        }

    for(i = 0; i < src_hsp_set->hsp_list->len; i++){
        src = src_hsp_set->hsp_list->pdata[i];
        hrtrd.src_hsp = src;
        hrtrd.src_hsp_id = i;
        RangeTree_find(rangetree,
                       HSP_query_cobs(src),
                       (HSP_query_cobs(src) - src->query_start)
                       + (HSP_query_cobs(max_dst_cobs_hsp) -
                           max_dst_cobs_hsp->query_start)
                       + max_query_join_range,
                       HSP_target_cobs(src),
                       (HSP_target_cobs(src) - src->target_start)
                       + (HSP_target_cobs(max_dst_cobs_hsp) -
                           max_dst_cobs_hsp->target_start)
                       + max_target_join_range,
                       HPair_RangeTree_ReportFunc, &hrtrd);
        }
    RangeTree_destroy(rangetree, NULL, NULL);
    return;
    }
