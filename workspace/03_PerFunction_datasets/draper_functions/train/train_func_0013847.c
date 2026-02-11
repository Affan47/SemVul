Analysis_find_matches(Analysis *analysis,
                       Match **dna_match, Match **protein_match,
                       Match **codon_match){
    register GPtrArray *transition_list
        = C4_Model_select_transitions(analysis->gam->model,
                                      C4_Label_MATCH);
    register gint i;
    register C4_Transition *transition;
    register Match *match;
    for(i = 0; i < transition_list->len; i++){
        transition = transition_list->pdata[i];
        g_assert(transition);
        g_assert(transition->label == C4_Label_MATCH);
        match = transition->label_data;
        if(match){
            switch(match->type){
                case Match_Type_DNA2DNA:
                    if((*dna_match) && ((*dna_match) != match))
                        g_error("Multiple DNA matches not implemented");
                    (*dna_match) = match;
                    break;
                case Match_Type_PROTEIN2PROTEIN:
                case Match_Type_DNA2PROTEIN:
                case Match_Type_PROTEIN2DNA:
                    if((*protein_match) && ((*protein_match) != match))
                        g_error("Multiple protein matches"
                                " not supported");
                    (*protein_match) = match;
                    break;
                case Match_Type_CODON2CODON:
                    if((*codon_match) && ((*codon_match) != match))
                        g_error("Multiple codon matches"
                                " not implemented");
                    (*codon_match) = match;
                    break;
                default:
                    break;
                }
            }
        }
    g_ptr_array_free(transition_list, TRUE);
    return;
    }
