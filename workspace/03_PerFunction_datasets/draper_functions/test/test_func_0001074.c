test_alignment(C4_Model *model,
                           Sequence *query, Sequence *target,
                           Protein2Genome_Data *p2gd){
    register C4_Score score;
    register Alignment *alignment;
    register Optimal *optimal = Optimal_create(model,
                                               NULL,
                                               Optimal_Type_SCORE
                                              |Optimal_Type_PATH,
                                              FALSE);
    register Region *region = Region_create(0, 0,
                                           query->len, target->len);
    score = Optimal_find_score(optimal, region, p2gd, NULL);
    g_message("Score is [%d] (expect 131)", score);
    g_assert(score == 129);
    alignment = Optimal_find_path(optimal, region, p2gd,
                                  C4_IMPOSSIBLY_LOW_SCORE, NULL);
    g_message("Alignment score is [%d]", alignment->score);
    Alignment_display(alignment, query, target,
                      NULL,
                      Protein2Genome_Data_get_submat(p2gd),
                      Protein2Genome_Data_get_translate(p2gd), stdout);
    g_assert(score == alignment->score);
    Alignment_destroy(alignment);
    Optimal_destroy(optimal);
    Region_destroy(region);
    return;
    }
