scheduler_suc_has_head_omsync( Block *bpt )
{
    Block *suc = get_task_by_static_scheduler( bpt,
                                               bpt->outer->hmdf,
                                               FALSE );
    if( suc == NULL )
        return FALSE;

    switch( suc->oneway_type ){
    case pMPB:
        return TRUE;

    case sMPB:
        if( suc->kind == SB ){
            return TRUE;

        }else{
            return( is_do_loop(suc)
                    && find_block_need_barrier_before_loop_start(suc)
                    && !pre_block_is_all_bMPB(suc) );
        }

    default:
        return FALSE;
    }
}
