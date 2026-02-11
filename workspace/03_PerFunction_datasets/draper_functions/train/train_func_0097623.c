SDP_Pair_create(SDP *sdp, SubOpt *subopt,
                          Comparison *comparison,
                          gpointer user_data){
    register SDP_Pair *sdp_pair = g_new(SDP_Pair, 1);
    g_assert(sdp);
    sdp_pair->sdp = SDP_share(sdp);
    g_assert(comparison);
    g_assert(Comparison_has_hsps(comparison));
    sdp_pair->comparison = Comparison_share(comparison);
    sdp_pair->user_data = user_data;
    sdp_pair->alignment_count = 0;
    sdp_pair->subopt = SubOpt_share(subopt);
    sdp_pair->seed_list = SDP_Pair_create_seed_list(comparison);
    sdp_pair->seed_list_by_score = NULL;
    sdp_pair->boundary = NULL;
    sdp_pair->last_score = C4_IMPOSSIBLY_LOW_SCORE;
    sdp_pair->fwd_straceback = STraceback_create(sdp->model, TRUE);
    sdp_pair->rev_straceback = STraceback_create(sdp->model, FALSE);
    return sdp_pair;
    }
