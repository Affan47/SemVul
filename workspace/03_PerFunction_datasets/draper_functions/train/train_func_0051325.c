search_and_remove_doacr_directive( Block *bpt )
{
    Statement *stm;
    Directive *dir, *dir_next;
    Directive_func *func, *func_next;

    for( stm = bpt->pre_head->stm_head; stm != NULL; stm = stm->next ){
        for( dir = stm->dir_pre_head; dir != NULL; dir = dir_next ){
	    dir_next = dir->next;
            for( func = dir->func; func != NULL; func = func_next ){
		func_next = func->next;
                if( func->id == MFOR_DOACROSS )
                    dir_remove_func( func );
            }
        }
    }
}
