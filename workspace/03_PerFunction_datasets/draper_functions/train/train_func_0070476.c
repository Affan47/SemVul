execute( Chuck_VM * vm, Chuck_VM_Shred * shred )
{
    t_CKUINT *& reg_sp = (t_CKUINT *&)shred->reg->sp;
    t_CKINT lhs = 0;
    Chuck_String ** rhs_ptr = NULL;


    pop_( reg_sp, 2 );

    rhs_ptr = (Chuck_String **)(*(reg_sp+1));

    lhs = (*(t_CKINT *)(reg_sp));


    if( !(*rhs_ptr) ) goto null_pointer;


    (*rhs_ptr)->str += ::itoa(lhs);


    push_( reg_sp, (t_CKUINT)(*rhs_ptr) );

    return;

null_pointer:

    fprintf( stderr,
        "[chuck](VM): NullPointerException: () in shred[id=%d:%s], PC=[%d]\n",
        shred->xid, shred->name.c_str(), shred->pc );
    goto done;

done:

    shred->is_running = FALSE;
    shred->is_done = TRUE;
}
