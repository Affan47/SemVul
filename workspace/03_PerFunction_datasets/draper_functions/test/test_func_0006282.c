HSP_Param_swap(HSP_Param *hsp_param){
    g_assert(hsp_param);
    return HSP_Param_create(Match_swap(hsp_param->match),
                            hsp_param->use_horizon);
    }
