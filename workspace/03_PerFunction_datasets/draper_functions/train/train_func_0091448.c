execute( Chuck_VM * vm, Chuck_VM_Shred * shred )
{
    t_CKUINT *& reg_sp = (t_CKUINT *&)shred->reg->sp;
    Chuck_String * lhs = NULL;
    Chuck_String * rhs = NULL;
    Chuck_String * result = NULL;


    pop_( reg_sp, 2 );

    lhs = (Chuck_String *)(*(reg_sp));

    rhs = (Chuck_String *)(*(reg_sp+1));


    if( !rhs || !lhs ) goto null_pointer;


    result = (Chuck_String *)instantiate_and_initialize_object( &t_string, shred );


    result->str = lhs->str + rhs->str;


    push_( reg_sp, (t_CKUINT)(result) );

    return;

null_pointer:

    fprintf( stderr,
        "[chuck](VM): NullPointerException: (string + string) in shred[id=%d:%s], PC=[%d]\n",
        shred->xid, shred->name.c_str(), shred->pc );
    goto done;

done:

    shred->is_running = FALSE;
    shred->is_done = TRUE;
}
