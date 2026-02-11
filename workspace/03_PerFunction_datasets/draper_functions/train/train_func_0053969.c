expr_dump(int level, struct expr *e)
{
    switch(e->expr_op)
    {
    case SYMBOL:
        LOG(level, ("expr 0x%08X symref %s\n", (u32)e, e->type.symref));
        break;
    case NUMBER:
        LOG(level, ("expr 0x%08X number %d\n", (u32)e, e->type.number));
        break;
    case vNEG:
        LOG(level, ("expr 0x%08X unary op %d, referring to 0x%08X\n",
                    (u32)e, e->expr_op, (u32)e->type.arg1));
    case LNOT:
        LOG(level, ("expr 0x%08X unary op %d, referring to 0x%08X\n",
                    (u32)e, e->expr_op, (u32)e->type.arg1));
        break;
    default:
        LOG(level, ("expr 0x%08X binary op %d, arg1 0x%08X, arg2 0x%08X\n",
                    (u32)e, e->expr_op, (u32)e->type.arg1, (u32)e->expr_arg2));

    }
}
