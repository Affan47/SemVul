C4_Model_select_transitions(C4_Model *model, C4_Label label){
    register gint i;
    register GPtrArray *list = g_ptr_array_new();
    register C4_Transition *transition;
    for(i = 0; i < model->transition_list->len; i++){
        transition = model->transition_list->pdata[i];
        if(transition->label == label)
            g_ptr_array_add(list, transition);
        }
    if(!list->len){
        g_ptr_array_free(list, TRUE);
        return NULL;
        }
    return list;
    }
