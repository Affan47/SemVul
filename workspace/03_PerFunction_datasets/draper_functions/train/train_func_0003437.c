new_expr_op2(i16 op, struct expr *arg1, struct expr *arg2)
{
    struct expr *val;

    if(op == vNEG ||
       op == LNOT ||
       op == NUMBER ||
       op == SYMBOL)
    {

        printf("op %d, vNEG %d, NUMBER %d, SYMBOL %d\n", op, vNEG, NUMBER, SYMBOL);
        LOG(LOG_ERROR, ("%d not allowed as binary operator\n", op));
        exit(1);
    }

    val = chunkpool_malloc(s_expr_pool);
    val->expr_op = op;
    val->type.arg1 = arg1;
    val->expr_arg2 = arg2;

    expr_dump(LOG_DEBUG, val);

    return val;
}
