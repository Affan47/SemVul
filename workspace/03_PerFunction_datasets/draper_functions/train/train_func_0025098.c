type_engine_check_exp_if( Chuck_Env * env, a_Exp_If exp_if )
{

    t_CKTYPE cond = type_engine_check_exp( env, exp_if->cond );
    t_CKTYPE if_exp = type_engine_check_exp( env, exp_if->if_exp );
    t_CKTYPE else_exp = type_engine_check_exp( env, exp_if->else_exp );


    if( !cond || !if_exp || !else_exp ) return NULL;


    if( !isa( cond, &t_int ) ) return NULL;


    if( !( *if_exp == *else_exp ) )
    {
        EM_error2( exp_if->linepos,
            "incompatible types '%s' and '%s' in if expression...",
            if_exp->c_name(), else_exp->c_name() );
        return NULL;
    }

    return if_exp;
}
