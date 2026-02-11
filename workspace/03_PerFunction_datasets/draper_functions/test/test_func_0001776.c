Model_Type_check_input(Model_Type type,
                                   Alphabet_Type query_type,
                                   Alphabet_Type target_type){
    switch(type){
        case Model_Type_UNGAPPED:
            break;
        case Model_Type_UNGAPPED_TRANS:
        case Model_Type_EST2GENOME:
        case Model_Type_CODING2CODING:
        case Model_Type_CODING2GENOME:
        case Model_Type_CDNA2GENOME:
        case Model_Type_GENOME2GENOME:
            if(query_type != Alphabet_Type_DNA)
                g_error("Expected DNA query (not %s) for model [%s]",
                        Alphabet_Type_get_name(query_type),
                        Model_Type_to_string(type));
            if(target_type != Alphabet_Type_DNA)
                g_error("Expected DNA target (not %s) for model [%s]",
                        Alphabet_Type_get_name(target_type),
                        Model_Type_to_string(type));
            break;
        case Model_Type_AFFINE_GLOBAL:
        case Model_Type_AFFINE_BESTFIT:
        case Model_Type_AFFINE_LOCAL:
        case Model_Type_AFFINE_OVERLAP:
        case Model_Type_NER:
            if(query_type != target_type)
                g_error("Expected similar sequence types for model"
                        " [%s] (not %s:%s)",
                       Model_Type_to_string(type),
                       Alphabet_Type_get_name(query_type),
                       Alphabet_Type_get_name(target_type));
            if(query_type == Alphabet_Type_UNKNOWN)
                g_error("Model [%s] cannot use unknown sequence type",
                        Model_Type_to_string(type));
            break;
        case Model_Type_PROTEIN2DNA:
        case Model_Type_PROTEIN2DNA_BESTFIT:
        case Model_Type_PROTEIN2GENOME:
        case Model_Type_PROTEIN2GENOME_BESTFIT:

            if(query_type != Alphabet_Type_PROTEIN)
                g_error(
                    "Expected protein query (not %s) for model [%s]",
                        Alphabet_Type_get_name(query_type),
                        Model_Type_to_string(type));
            if(target_type != Alphabet_Type_DNA)
                g_error("Expected DNA target (not %s) for model [%s]",
                        Alphabet_Type_get_name(target_type),
                        Model_Type_to_string(type));
            break;
        default:
            g_error("Unknown model type [%s]",
                    Model_Type_to_string(type));
            break;
        }
    return;
    }
