gwy_expr_transform_values(GwyExpr *expr)
{
    GwyExprToken *code, *t;
    GQuark quark;
    gdouble *cval;
    guint i;

    if (!expr->identifiers) {
        expr->identifiers = g_ptr_array_new();

        g_ptr_array_add(expr->identifiers, NULL);
    }
    else
        g_ptr_array_set_size(expr->identifiers, 1);

    for (t = expr->tokens; t; t = t->next) {
        if (t->token == G_TOKEN_FLOAT) {
            code = gwy_expr_token_new0(expr);
            code->token = GWY_EXPR_CODE_CONSTANT;
            code->value.v_float = t->value.v_float;
            t->rpn_block = gwy_expr_token_list_prepend(t->rpn_block, code);
            continue;
        }
        else if (t->token != G_TOKEN_IDENTIFIER)
            continue;

        if (expr->constants) {
            if ((quark = g_quark_try_string(t->value.v_identifier))
                && (cval = g_hash_table_lookup(expr->constants,
                                               GUINT_TO_POINTER(quark)))) {
                code = gwy_expr_token_new0(expr);
                code->token = GWY_EXPR_CODE_CONSTANT;
                code->value.v_float = *cval;
                t->rpn_block = gwy_expr_token_list_prepend(t->rpn_block, code);
                continue;
            }
        }
        for (i = 1; i < expr->identifiers->len; i++) {
            if (strcmp(t->value.v_identifier,
                       g_ptr_array_index(expr->identifiers, i)) == 0) {
                g_free(t->value.v_identifier);
                break;
            }
        }
        if (i == expr->identifiers->len)
            g_ptr_array_add(expr->identifiers, t->value.v_identifier);
        code = gwy_expr_token_new0(expr);
        code->token = -i;
        t->rpn_block = gwy_expr_token_list_prepend(t->rpn_block, code);
    }

    return TRUE;
}
