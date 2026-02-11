insert_doacross_directive(StripMining *sm, Loop *sm_loop)
{

    if (sm->flg_doacross)
        put_doacross_directive(sm_loop->block);
    else
        sm_loop->block->kind = sm->pe_loop_kind;

}
