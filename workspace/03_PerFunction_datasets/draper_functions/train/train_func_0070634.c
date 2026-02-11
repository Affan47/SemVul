Affine_Data_init(Affine_Data *ad,
                      Sequence *query, Sequence *target,
                      gboolean translate_both){
    register Match_Type match_type
        = Match_Type_find(query->alphabet->type,
                          target->alphabet->type,
                          translate_both);
    Ungapped_Data_init(&ad->ud, query, target, match_type);
    if(!ad->aas)
        ad->aas = Affine_ArgumentSet_create(NULL);
    return;
    }
