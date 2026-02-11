GAM_Result_BSDP_add_HSPset(HSPset *hspset, GAM *gam,
                                       HPair *hpair){
    register C4_Portal *portal;
    portal = GAM_Pair_find_portal(gam->model, hspset);
    HPair_add_hspset(hpair, portal, hspset);
    if(gam->verbosity > 2)
        g_message("Added [%d] hsps to HPair",
                  hspset->hsp_list->len);
    return;
    }
