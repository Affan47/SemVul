ExecAssLVar15 (
    Stat                stat )
{
    Obj                 rhs;


    SET_BRK_CURR_STAT( stat );
    rhs = EVAL_EXPR( ADDR_STAT(stat)[1] );
    ASS_LVAR( 15, rhs );


    return 0;
}
