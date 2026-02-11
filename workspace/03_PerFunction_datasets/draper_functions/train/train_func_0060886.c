Optimal_create(C4_Model *model, gchar *name,
                        Optimal_Type type, gboolean use_codegen){
    register Optimal *optimal = g_new0(Optimal, 1);
    register gchar *viterbi_name;
    g_assert(model);
    g_assert(!model->is_open);
    optimal->ref_count = 1;
    if(name)
        optimal->name = g_strdup(name);
    else
        optimal->name = g_strdup_printf("optimal:%s", model->name);
    optimal->type = type;
    if(type & Optimal_Type_SCORE){
        viterbi_name = g_strconcat(optimal->name, " find score", NULL);
        optimal->find_score = Viterbi_create(model, viterbi_name,
                              Viterbi_Mode_FIND_SCORE, FALSE,
                              use_codegen);
        g_free(viterbi_name);
        }
    if(type & Optimal_Type_PATH){
        viterbi_name = g_strconcat(optimal->name, " find path", NULL);
        optimal->find_path = Viterbi_create(model, viterbi_name,
                             Viterbi_Mode_FIND_PATH, FALSE,
                             use_codegen);
        g_free(viterbi_name);
        }
    if(type & Optimal_Type_REDUCED_SPACE){
        if(!C4_Model_is_global(model)){
            viterbi_name = g_strconcat(optimal->name, " find region",
                                      NULL);
            optimal->find_region = Viterbi_create(model, viterbi_name,
                                      Viterbi_Mode_FIND_REGION, FALSE,
                                      use_codegen);
            g_free(viterbi_name);
            }
        viterbi_name = g_strconcat(optimal->name,
                                  " find checkpoint", NULL);
        optimal->find_checkpoint_continuation
           = Viterbi_create(model, viterbi_name,
                     Viterbi_Mode_FIND_CHECKPOINTS, TRUE, use_codegen);
        g_free(viterbi_name);
        viterbi_name = g_strconcat(optimal->name,
                                  " find path continuation", NULL);
        optimal->find_path_continuation
           = Viterbi_create(model, viterbi_name,
                     Viterbi_Mode_FIND_PATH, TRUE, use_codegen);
        g_free(viterbi_name);

        }
    return optimal;
    }
