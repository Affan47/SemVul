C4_Model_configure_start_state(C4_Model *model, C4_Scope scope,
        C4_CellStartFunc cell_start_func, gchar *cell_start_macro){
    g_assert(model);


    model->start_state->scope = scope;
    model->start_state->cell_start_func = cell_start_func;
    if(model->start_state->cell_start_macro != cell_start_macro){
        if(model->start_state->cell_start_macro)
            g_free(model->start_state->cell_start_macro);
        if(cell_start_macro)
            model->start_state->cell_start_macro
                                     = g_strdup(cell_start_macro);
        else
            model->start_state->cell_start_macro = NULL;
    } else {
        model->start_state->cell_start_macro = NULL;
        }
    return;
    }
