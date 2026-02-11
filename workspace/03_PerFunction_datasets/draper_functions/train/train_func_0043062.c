Affine_Data_create(Sequence *query, Sequence *target,
                                gboolean translate_both){
    register Affine_Data *ad = g_new0(Affine_Data, 1);
    Affine_Data_init(ad, query, target, translate_both);
    return ad;
    }
