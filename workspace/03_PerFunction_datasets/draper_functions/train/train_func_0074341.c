emit_engine_emit_exp_cast( Chuck_Emitter * emit, a_Exp_Cast cast )
{
    Chuck_Type * to = cast->self->type;
    Chuck_Type * from = cast->exp->type;


    if( !emit_engine_emit_exp( emit, cast->exp ) )
        return FALSE;


    return emit_engine_emit_cast( emit, to, from );
}
