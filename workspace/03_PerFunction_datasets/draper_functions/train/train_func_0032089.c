Seeder_add_WordInfo(Seeder *seeder, gchar *word,
                                            Seeder_Context *context){
    register Seeder_WordInfo *word_info;
    register VFSM_Int state = 0, leaf;
    if(seeder->seeder_fsm){
        word_info = Seeder_WordInfo_create(seeder);
        word_info = FSM_add(seeder->seeder_fsm->fsm, word,
                            context->loader->hsp_param->wordlen, word_info);
    } else {
        g_assert(seeder->seeder_vfsm);
        state = VFSM_word2state(seeder->seeder_vfsm->vfsm, word);
        leaf = VFSM_state2leaf(seeder->seeder_vfsm->vfsm, state);
        word_info = seeder->seeder_vfsm->leaf[leaf];
        if(!word_info){
            word_info = Seeder_WordInfo_create(seeder);
            seeder->seeder_vfsm->leaf[leaf] = word_info;
            }
        }
    return word_info;
    }
