OPair_next_path(OPair *opair, C4_Score threshold){
    register Alignment *alignment;
    alignment = Optimal_find_path(opair->optimal, opair->region,
                                  opair->user_data, threshold,
                                  opair->subopt);
    if(alignment){
        if(alignment->score > opair->prev_score)
            g_warning("Score [%d] greater than previous [%d]",
                      alignment->score, opair->prev_score);
        g_assert(alignment->score <= opair->prev_score);
        opair->prev_score = alignment->score;
        }
    return alignment;
    }
