make_exprt(enum expr_type type, var_t *var, expr_t *expr)
{
    expr_t *e;
    type_t *tref;

    if (var->stgclass != STG_NONE && var->stgclass != STG_REGISTER)
        error_loc("invalid storage class for type expression\n");

    tref = var->type;

    e = xmalloc(sizeof(expr_t));
    e->type = type;
    e->ref = expr;
    e->u.tref = tref;
    e->is_const = FALSE;
    if (type == EXPR_SIZEOF)
    {

        if (is_integer_type(tref) || is_float_type(tref))
        {
            e->is_const = TRUE;
            e->cval = type_memsize(tref);
        }
    }

    if (type == EXPR_CAST && expr->is_const)
    {
        if (is_integer_type(tref))
        {
            unsigned int cast_type_bits = type_memsize(tref) * 8;
            unsigned int cast_mask;

            e->is_const = TRUE;
            if (is_signed_integer_type(tref))
            {
                cast_mask = (1 << (cast_type_bits - 1)) - 1;
                if (expr->cval & (1 << (cast_type_bits - 1)))
                    e->cval = -((-expr->cval) & cast_mask);
                else
                    e->cval = expr->cval & cast_mask;
            }
            else
            {

                cast_mask = ((1 << (cast_type_bits - 1)) - 1) |
                            1 << (cast_type_bits - 1);
                e->cval = expr->cval & cast_mask;
            }
        }
        else
        {
            e->is_const = TRUE;
            e->cval = expr->cval;
        }
    }
    free(var);
    return e;
}
