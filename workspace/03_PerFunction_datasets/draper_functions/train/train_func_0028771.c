prepend_array_sub( a_Array_Sub a, a_Exp exp, int pos )
{

    if( a->err_num ) goto error;


    if( exp && exp->next )
    {
        a->err_num = 1;
        a->err_pos = exp->linepos;
        goto error;
    }


    if( (exp && !a->exp_list) || (!exp && a->exp_list) )
    {
        a->err_num = 2;
        a->err_pos = pos;
        goto error;
    }


    if( exp )
    {
        exp->next = a->exp_list;
        a->exp_list = exp;
    }


    a->depth++;
    return a;

error:
    clean_exp( exp );
    return a;
}
