C4_Model_finalise(C4_Model *model){
    register gint i;
    register C4_Portal *portal;
    register C4_Transition *transition;
    g_assert(model);
    for(i = 0; i < model->portal_list->len; i++){
        portal = model->portal_list->pdata[i];
        if(portal->transition_list->len)
            g_ptr_array_set_size(portal->transition_list, 0);
        C4_Portal_find_transitions(portal, model);
        }
    model->max_query_advance = 0;
    model->max_target_advance = 0;
    for(i = 0; i < model->transition_list->len; i++){
        transition = model->transition_list->pdata[i];
        if(model->max_query_advance < transition->advance_query)
            model->max_query_advance = transition->advance_query;
        if(model->max_target_advance < transition->advance_target)
            model->max_target_advance = transition->advance_target;
        }
    g_assert(model->max_query_advance || model->max_target_advance);
    return;
    }
