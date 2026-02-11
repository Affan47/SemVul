C4_Model_insert_shadows(C4_Model *target,
                                    C4_Model *insert,
                                    C4_State *src, C4_State *dst,
                                    C4_State **state_map,
                                    C4_Transition **transition_map){
    register gint i, j;
    register C4_Shadow *shadow, *new_shadow;
    register C4_State *state, *src_state;
    register C4_Transition *transition, *dst_transition;

    for(i = 0; i < insert->shadow_list->len; i++){
        shadow = insert->shadow_list->pdata[i];
        g_assert(shadow);
        g_assert(shadow->src_state_list->len);
        g_assert(shadow->dst_transition_list->len);
        state = shadow->src_state_list->pdata[0];
        src_state = state_map[state->id];
        transition = shadow->dst_transition_list->pdata[0];
        dst_transition = transition_map[transition->id];
        new_shadow = C4_Model_add_shadow(target, shadow->name,
              src_state, dst_transition,
              shadow->start_func, shadow->start_macro,
              shadow->end_func, shadow->end_macro);
        for(j = 1; j < shadow->src_state_list->len; j++){
            state = shadow->src_state_list->pdata[j];
            src_state = state_map[state->id];
            C4_Shadow_add_src_state(new_shadow, src_state);
            }
        for(j = 1; j < shadow->dst_transition_list->len; j++){
            transition = shadow->dst_transition_list->pdata[j];
            dst_transition = transition_map[transition->id];
            C4_Shadow_add_dst_transition(new_shadow, dst_transition);
            }
        }
    return;
    }
