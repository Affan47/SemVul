Coding2Coding_Data_init(Coding2Coding_Data *c2cd,
                           Sequence *query, Sequence *target){
    g_assert(query->alphabet->type == Alphabet_Type_DNA);
    g_assert(target->alphabet->type == Alphabet_Type_DNA);
    Affine_Data_init(&c2cd->ad, query, target, TRUE);
    if(!Coding2Coding_Data_get_Frameshift_Data(c2cd))
        Coding2Coding_Data_get_Frameshift_Data(c2cd)
              = Frameshift_Data_create();
    return;
    }
