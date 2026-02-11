GAM_Result_destroy(GAM_Result *gam_result){
    register gint i;
    if(--gam_result->ref_count)
        return;
    if(gam_result->alignment_list){
        for(i = 0; i < gam_result->alignment_list->len; i++)
            Alignment_destroy(gam_result->alignment_list->pdata[i]);
        g_ptr_array_free(gam_result->alignment_list, TRUE);
        }
    Model_Type_destroy_data(gam_result->gam->gas->type,
                            gam_result->user_data);
    Sequence_destroy(gam_result->query);
    Sequence_destroy(gam_result->target);
    GAM_destroy(gam_result->gam);
    SubOpt_destroy(gam_result->subopt);
    g_free(gam_result);
    return;
    }
