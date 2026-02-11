type_engine_check_array_subscripts( Chuck_Env * env, a_Exp exp_list )
{
    a_Exp exp = exp_list;


    while( exp )
    {

        if( !isa( exp->type, &t_int ) )
        {
            EM_error2( exp->linepos,
                "incompatible array subscript type '%s'...",
                exp->type->name.c_str() );
            return FALSE;
        }

        exp = exp->next;
    }

    return TRUE;
}
