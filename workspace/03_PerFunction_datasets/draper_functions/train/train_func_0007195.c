Comparison_Param_create_without_mirror(
                                          Alphabet_Type query_type,
                                          Alphabet_Type target_type,
                                          HSP_Param *dna_hsp_param,
                                          HSP_Param *protein_hsp_param,
                                          HSP_Param *codon_hsp_param,
                                          gboolean swap_param){
    register Comparison_Param *param = g_new(Comparison_Param, 1);
    param->ref_count = 1;
    param->query_type = query_type;
    param->target_type = target_type;
    param->dna_hsp_param = Comparison_Param_get_hsp_param(dna_hsp_param,
                                                          swap_param);
    param->protein_hsp_param = Comparison_Param_get_hsp_param(protein_hsp_param,
                                                              swap_param);
    param->codon_hsp_param = Comparison_Param_get_hsp_param(codon_hsp_param,
                                                            swap_param);
    param->mirror = NULL;
    return param;
    }
