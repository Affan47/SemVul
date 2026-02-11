emit_engine_emit_loop( Chuck_Emitter * emit, a_Stmt_Loop stmt )
{
    t_CKBOOL ret = TRUE;
    Chuck_Instr_Branch_Op * op = NULL;

    t_CKINT * counter = NULL;


    emit->push_scope();


    ret = emit_engine_emit_exp( emit, stmt->cond );
    if( !ret )
        return FALSE;


    emit->append( new Chuck_Instr_Init_Loop_Counter( (t_CKUINT)(counter = new t_CKINT) ) );


    t_CKUINT start_index = emit->next_index();

    emit->code->stack_cont.push_back( NULL );

    emit->code->stack_break.push_back( NULL );


    emit->append( new Chuck_Instr_Reg_Push_Deref( (t_CKUINT)counter, sz_INT ) );


    Chuck_Type * type = stmt->cond->cast_to ? stmt->cond->cast_to : stmt->cond->type;


    switch( type->xid )
    {
    case te_int:

        emit->append( new Chuck_Instr_Reg_Push_Imm( 0 ) );
        op = new Chuck_Instr_Branch_Eq_int( 0 );
        break;

    default:
        EM_error2( stmt->cond->linepos,
            "(emit): internal error: unhandled type '%s' in while conditional",
            type->name.c_str() );

        return FALSE;
    }


    emit->append( op );


    emit->append( new Chuck_Instr_Dec_int_Addr( (t_CKUINT)counter ) );


    ret = emit_engine_emit_stmt( emit, stmt->body );
    if( !ret )
        return FALSE;


    emit->append( new Chuck_Instr_Goto( start_index ) );


    op->set( emit->next_index() );


    while( emit->code->stack_cont.size() && emit->code->stack_cont.back() )
    {
        emit->code->stack_cont.back()->set( start_index );
        emit->code->stack_cont.pop_back();
    }


    while( emit->code->stack_break.size() && emit->code->stack_break.back() )
    {
        emit->code->stack_break.back()->set( emit->next_index() );
        emit->code->stack_break.pop_back();
    }


    emit->pop_scope();

    emit->code->stack_cont.pop_back();

    emit->code->stack_break.pop_back();

    return ret;
}
