compare_expr(const expr_t *a, const expr_t *b)
{
    int ret;

    if (a->type != b->type)
        return a->type - b->type;

    switch (a->type)
    {
        case EXPR_NUM:
        case EXPR_HEXNUM:
        case EXPR_TRUEFALSE:
            return a->u.lval - b->u.lval;
        case EXPR_DOUBLE:
            return a->u.dval - b->u.dval;
        case EXPR_IDENTIFIER:
        case EXPR_STRLIT:
        case EXPR_WSTRLIT:
        case EXPR_CHARCONST:
            return strcmp(a->u.sval, b->u.sval);
        case EXPR_COND:
            ret = compare_expr(a->ref, b->ref);
            if (ret != 0)
                return ret;
            ret = compare_expr(a->u.ext, b->u.ext);
            if (ret != 0)
                return ret;
            return compare_expr(a->ext2, b->ext2);
        case EXPR_OR:
        case EXPR_AND:
        case EXPR_ADD:
        case EXPR_SUB:
        case EXPR_MOD:
        case EXPR_MUL:
        case EXPR_DIV:
        case EXPR_SHL:
        case EXPR_SHR:
        case EXPR_MEMBER:
        case EXPR_ARRAY:
        case EXPR_LOGOR:
        case EXPR_LOGAND:
        case EXPR_XOR:
        case EXPR_EQUALITY:
        case EXPR_INEQUALITY:
        case EXPR_GTR:
        case EXPR_LESS:
        case EXPR_GTREQL:
        case EXPR_LESSEQL:
            ret = compare_expr(a->ref, b->ref);
            if (ret != 0)
                return ret;
            return compare_expr(a->u.ext, b->u.ext);
        case EXPR_CAST:
            ret = compare_type(a->u.tref, b->u.tref);
            if (ret != 0)
                return ret;

        case EXPR_NOT:
        case EXPR_NEG:
        case EXPR_PPTR:
        case EXPR_ADDRESSOF:
        case EXPR_LOGNOT:
        case EXPR_POS:
            return compare_expr(a->ref, b->ref);
        case EXPR_SIZEOF:
            return compare_type(a->u.tref, b->u.tref);
        case EXPR_VOID:
            return 0;
    }
    return -1;
}
