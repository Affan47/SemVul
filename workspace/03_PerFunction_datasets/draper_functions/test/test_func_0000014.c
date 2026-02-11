HPair_destroy(HPair *hpair){
    register gint i;
    register HSPset *hspset;
    for(i = 0; i < hpair->portal_data_list->len; i++){
        hspset= hpair->portal_data_list->pdata[i];
        if(hspset)
            HSPset_destroy(hspset);
        }
    g_ptr_array_free(hpair->portal_data_list, TRUE);
    HPair_destroy_offset_list(hpair);
    BSDP_destroy(hpair->bsdp);
    Heuristic_destroy(hpair->heuristic);
    SubOpt_destroy(hpair->subopt);
    g_free(hpair);
    return;
    }
