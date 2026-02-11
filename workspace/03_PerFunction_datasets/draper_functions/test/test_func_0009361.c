GAM_Result_ungapped_add_HSPset(GAM_Result *gam_result,
                                           C4_Model *model,
                                           HSPset *hspset){
    register gint i;
    register C4_Score threshold;
    register Alignment *alignment;
    register HSP *hsp;
    HSPset_filter_ungapped(hspset);
    for(i = 0; i < hspset->hsp_list->len; i++){
        hsp = hspset->hsp_list->pdata[i];
        threshold = GAM_get_query_threshold(gam_result->gam, hspset->query);
        if(hsp->score >= threshold){
            alignment = Ungapped_Alignment_create(model,
                                                  gam_result->user_data,
                                                  hsp);
            g_assert(alignment);
            GAM_Result_add_alignment(gam_result, alignment, threshold);
            }
        }
    return;
    }
