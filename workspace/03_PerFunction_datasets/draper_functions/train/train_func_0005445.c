HPair_initialise_bsdp_edges(HPair *hpair){
    register gint i, j;
    register Heuristic_Pair *pair;
    gint edge_total = 0;
    for(i = 0; i < hpair->heuristic->match_total; i++){
        for(j = 0; j < hpair->heuristic->match_total; j++){
            pair = hpair->heuristic->pair_matrix[i][j];
            if(pair)
                HPair_find_candidate_hsp_pairs(hpair, pair,
                                               &edge_total);
            }
        }
    if(hpair->verbosity > 1)
        g_message("Built HPair using [%d] edges", edge_total);
    return;
    }
