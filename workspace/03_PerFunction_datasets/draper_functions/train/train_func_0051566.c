SAR_find_cobs_box(HSP *src, HSP *dst, Region *region){
    region->query_start = HSP_query_cobs(src);
    region->target_start = HSP_target_cobs(src);
    region->query_length = HSP_query_cobs(dst)
                         - region->query_start;
    region->target_length = HSP_target_cobs(dst)
                          - region->target_start;
    if(region->query_length <= 0)
        return FALSE;
    if(region->target_length <= 0)
        return FALSE;
    return TRUE;
    }
