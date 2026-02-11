SAR_Terminal_calculate_start_region(HSP *hsp,
            HPair *hpair, Heuristic_Range *range, C4_Scope scope,
            Region *region){
    register gint to_shrink;
    register gboolean at_query_edge = FALSE, at_target_edge = FALSE;
    Region outer_box;

    outer_box.query_start = 0;
    outer_box.target_start = 0;
    outer_box.query_length = HSP_query_cobs(hsp);
    outer_box.target_length = HSP_target_cobs(hsp);

    region->query_start = hsp->query_start;
    region->target_start = hsp->target_start;
    region->query_length = 0;
    region->target_length = 0;

    region->query_start -= range->external_query;
    region->target_start -= range->external_target;
    region->query_length += range->external_query;
    region->target_length += range->external_target;

    region->query_length += range->internal_query;
    region->target_length += range->internal_target;

    if(region->query_start < outer_box.query_start){
        region->query_length -= (outer_box.query_start
                                 - region->query_start);
        region->query_start = outer_box.query_start;
        }
    if(region->target_start < outer_box.target_start){
        region->target_length -= (outer_box.target_start
                                  - region->target_start);
        region->target_start = outer_box.target_start;
        }
    to_shrink = Region_query_end(region)
              - Region_query_end(&outer_box);
    if(to_shrink > 0)
        region->query_length -= to_shrink;
    to_shrink = Region_target_end(region)
              - Region_target_end(&outer_box);
    if(to_shrink > 0)
        region->target_length -= to_shrink;

    if(region->query_length <= 0)
        return FALSE;
    if(region->target_length <= 0)
        return FALSE;

    g_assert(SAR_region_valid_hsp_exit(region, hsp));

    at_query_edge = (region->query_start == 0);
    at_target_edge = (region->target_start == 0);
    switch(scope){
        case C4_Scope_ANYWHERE:
            return TRUE;
            break;
        case C4_Scope_CORNER:
            if(at_query_edge && at_target_edge)
                return TRUE;
            break;
        case C4_Scope_EDGE:
            if(at_query_edge || at_target_edge)
                return TRUE;
            break;
        case C4_Scope_QUERY:
            if(at_query_edge)
                return TRUE;
            break;
        case C4_Scope_TARGET:
            if(at_target_edge)
                return TRUE;
            break;
        }
    return FALSE;
    }
