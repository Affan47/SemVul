type_engine_check_exp_dot_member( Chuck_Env * env, a_Exp_Dot_Member member )
{
    Chuck_Value * value = NULL;
    Chuck_Type * the_base = NULL;
    t_CKBOOL base_static = FALSE;
    string str;


    member->t_base = type_engine_check_exp( env, member->base );
    if( !member->t_base ) return NULL;


    base_static = isa( member->t_base, &t_class );

    the_base = base_static ? member->t_base->actual_type : member->t_base;


    if( !the_base->info )
    {

        EM_error2( member->base->linepos,
            "type '%s' does not have members - invalid use in dot expression",
            the_base->c_name() );
        return NULL;
    }


    str = S_name(member->xid);
    if( str == "this" )
    {

        if( base_static )
        {
            EM_error2( member->linepos,
                "keyword 'this' must be associated with object instance..." );
            return NULL;
        }

        if( env->func && !env->func->is_member )
        {
            EM_error2( member->linepos,
                "keyword 'this' cannot be used inside static functions..." );
            return NULL;
        }

        return env->class_def;
    }


    value = type_engine_find_value( the_base, member->xid );
    if( !value )
    {

        EM_error2( member->base->linepos,
            "class '%s' has no member '%s'",
            the_base->c_name(), S_name(member->xid) );
        return NULL;
    }


    if( base_static && value->is_member )
    {

        EM_error2( member->linepos,
            "cannot access member '%s.%s' without object instance...",
            the_base->c_name(), S_name(member->xid) );
        return NULL;
    }

    return value->type;
}
