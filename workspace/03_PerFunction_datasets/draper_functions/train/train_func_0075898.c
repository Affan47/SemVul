find_send_recv_directive(Block* block_head)
{
    Block *bpt;
    Statement *stm;
    Directive *dir;
    Directive_func *d_func;

    for(bpt = block_head; bpt != NULL; bpt = bpt->next){
        if (bpt->pre_head != NULL) {

            for( stm = bpt->pre_head->stm_head;
                 stm != NULL;
                 stm = stm->next ){
                for( dir = stm->dir_pre_head;
                     dir != NULL;
                     dir = dir->next ){
                    for( d_func = dir->func;
                         d_func != NULL;
                         d_func = d_func->next ){
                        if( d_func->id == MFOR_DOACROSS_SENDER
                            || d_func->id == MFOR_DOACROSS_RECEIVER )
                            return d_func;
                    }
                }
            }
        }

        if (bpt->inner != NULL) {
            d_func = find_send_recv_directive(bpt->inner);
            if (d_func != NULL)
                return d_func;
        }
    }

    return NULL;
}
