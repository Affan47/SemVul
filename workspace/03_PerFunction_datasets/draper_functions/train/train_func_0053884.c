HSPset_revcomp(HSPset *hsp_set){
    register Sequence *rc_query = Sequence_revcomp(hsp_set->query),
                      *rc_target = Sequence_revcomp(hsp_set->target);
    register gint i;
    register HSP *hsp;
    g_assert(hsp_set);
    g_assert(hsp_set->is_finalised);
    g_assert(hsp_set->ref_count == 1);

    Sequence_destroy(hsp_set->query);
    Sequence_destroy(hsp_set->target);
    hsp_set->query = rc_query;
    hsp_set->target = rc_target;
    for(i = 0; i < hsp_set->hsp_list->len; i++){
        hsp = hsp_set->hsp_list->pdata[i];
        hsp->query_start = hsp_set->query->len - HSP_query_end(hsp);
        hsp->target_start = hsp_set->target->len - HSP_target_end(hsp);
        }
    return;
    }
