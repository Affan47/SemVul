Seeder_FSM_create(Seeder *seeder){
    register Seeder_FSM *seeder_fsm = g_new(Seeder_FSM, 1);
    register Match *match = seeder->any_hsp_param->match;
    seeder_fsm->fsm
            = FSM_create((gchar*)match->comparison_alphabet->member,
                                 Seeder_FSM_merge_func,
                                 Seeder_FSM_combine_func,
                                 seeder);
    return seeder_fsm;
    }
