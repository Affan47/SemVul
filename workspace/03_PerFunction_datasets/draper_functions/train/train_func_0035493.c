Model_Type_create_data(Model_Type type,
                                Sequence *query, Sequence *target){
    register gpointer model_data = NULL;
    register Match_Type match_type;
    switch(type){
        case Model_Type_UNGAPPED:
            match_type = Match_Type_find(query->alphabet->type,
                                         target->alphabet->type,
                                         FALSE);
            model_data = Ungapped_Data_create(query, target,
                                              match_type);
            break;
        case Model_Type_UNGAPPED_TRANS:
            match_type = Match_Type_find(query->alphabet->type,
                                         target->alphabet->type,
                                         TRUE);
            model_data = Ungapped_Data_create(query, target,
                                              match_type);
            break;
        case Model_Type_AFFINE_GLOBAL:

        case Model_Type_AFFINE_BESTFIT:

        case Model_Type_AFFINE_LOCAL:

        case Model_Type_AFFINE_OVERLAP:
            model_data = Affine_Data_create(query, target, FALSE);
            break;
        case Model_Type_EST2GENOME:
            model_data = EST2Genome_Data_create(query, target);
            break;
        case Model_Type_NER:
            model_data = NER_Data_create(query, target);
            break;
        case Model_Type_PROTEIN2DNA:

        case Model_Type_PROTEIN2DNA_BESTFIT:
            model_data = Protein2DNA_Data_create(query, target);
            break;
        case Model_Type_PROTEIN2GENOME:

        case Model_Type_PROTEIN2GENOME_BESTFIT:
            model_data = Protein2Genome_Data_create(query, target);
            break;
        case Model_Type_CODING2CODING:
            model_data = Coding2Coding_Data_create(query, target);
            break;
        case Model_Type_CODING2GENOME:
            model_data = Coding2Genome_Data_create(query, target);
            break;
        case Model_Type_CDNA2GENOME:
            model_data = CDNA2Genome_Data_create(query, target);
            break;
        case Model_Type_GENOME2GENOME:
            model_data = Genome2Genome_Data_create(query, target);
            break;
        default:
            g_error("Unknown Model Type [%d]", type);
        }
    return model_data;
    }
