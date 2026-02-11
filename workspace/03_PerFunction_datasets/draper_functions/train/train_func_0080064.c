SAR_Alignment_create(SAR_Terminal *sar_start,
                                    SAR_Terminal *sar_end,
                                    Heuristic_Match *start_match,
                                    Heuristic_Match *end_match,
                                    HPair *hpair, C4_Score score){
    register SAR_Alignment *sar_alignment = g_new(SAR_Alignment, 1);
    register Region *align_region;
    register Alignment *start_alignment
      = Optimal_find_path(start_match->start_terminal->optimal,
                          sar_start->region, hpair->user_data,
                          C4_IMPOSSIBLY_LOW_SCORE, hpair->subopt);
    g_assert(start_alignment);
    sar_alignment->end_alignment
      = Optimal_find_path(end_match->end_terminal->optimal,
                          sar_end->region, hpair->user_data,
                          C4_IMPOSSIBLY_LOW_SCORE, hpair->subopt);
    sar_alignment->end_region = Region_share(sar_end->region);
    sar_alignment->end_match = end_match;
    g_assert(sar_alignment->end_alignment);
    align_region = Region_create(start_alignment->region->query_start,
                                 start_alignment->region->target_start,
        Region_query_end(sar_alignment->end_alignment->region)
        - start_alignment->region->query_start,
        Region_target_end(sar_alignment->end_alignment->region)
        - start_alignment->region->target_start);
    sar_alignment->alignment = Alignment_create(hpair->heuristic->model,
                                                align_region, score);
    Alignment_import_derived(sar_alignment->alignment, start_alignment,
                           start_match->start_terminal->terminal_model);
    sar_alignment->hpair = hpair;
    sar_alignment->last_region = Region_share(start_alignment->region);
    sar_alignment->last_hsp = NULL;
    sar_alignment->last_match = NULL;
    Alignment_destroy(start_alignment);
    Region_destroy(align_region);
    return sar_alignment;
    }
