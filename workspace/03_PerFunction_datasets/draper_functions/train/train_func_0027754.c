load_gla(struct bc_read_stream *s, struct gla *gla, struct grammar *g)
{

    gla->num_states = 0;
    gla->num_transitions = 0;

    while(1)
    {
        struct record_info ri = bc_rs_next_data_record(s);
        if(ri.record_type == DataRecord)
        {
            if(ri.id == BC_GLA_STATE ||
               ri.id == BC_GLA_FINAL_STATE)
                gla->num_states++;
            else if(ri.id == BC_GLA_TRANSITION)
                gla->num_transitions++;
        }
        else if(ri.record_type == EndBlock)
            break;
        else
            unexpected(s, ri);
    }

    bc_rs_rewind_block(s);
    gla->states = malloc(gla->num_states * sizeof(*gla->states));
    gla->transitions = malloc(gla->num_transitions * sizeof(*gla->transitions));

    int state_offset = 0;
    int transition_offset = 0;
    int state_transition_offset = 0;

    while(1)
    {
        struct record_info ri = bc_rs_next_data_record(s);
        if(ri.record_type == DataRecord)
        {
            if(ri.id == BC_GLA_STATE || ri.id == BC_GLA_FINAL_STATE)
            {
                struct gla_state *state = &gla->states[state_offset++];

                if(ri.id == BC_GLA_STATE)
                {
                    state->is_final = false;
                    state->d.nonfinal.intfa = &g->intfas[bc_rs_read_next_32(s)];
                    state->d.nonfinal.num_transitions = bc_rs_read_next_32(s);
                    state->d.nonfinal.transitions = &gla->transitions[state_transition_offset];
                    state_transition_offset += state->d.nonfinal.num_transitions;
                }
                else
                {
                    state->is_final = true;
                    state->d.final.transition_offset = bc_rs_read_next_32(s);
                }
            }
            else if(ri.id == BC_GLA_TRANSITION)
            {
                struct gla_transition *transition = &gla->transitions[transition_offset++];
                int term = bc_rs_read_next_32(s);
                int dest_state_offset = bc_rs_read_next_32(s);
                transition->dest_state = &gla->states[dest_state_offset];
                if(term == 0)
                    transition->term = NULL;
                else
                    transition->term = g->strings[term-1];
            }
        }
        else if(ri.record_type == EndBlock)
            break;
        else
            unexpected(s, ri);
    }
}
