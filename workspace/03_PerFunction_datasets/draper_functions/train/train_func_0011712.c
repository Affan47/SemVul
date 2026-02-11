gwy_expr_transform_to_rpn(GwyExpr *expr,
                          GError **err)
{
    GwyExprToken *t;
    guint i;


    t = gwy_expr_token_new0(expr);
    t->token = G_TOKEN_RIGHT_PAREN;
    expr->tokens = gwy_expr_token_list_concat(expr->tokens, t);
    t = gwy_expr_token_new0(expr);
    t->token = G_TOKEN_LEFT_PAREN;
    expr->tokens = gwy_expr_token_list_prepend(expr->tokens, t);

    expr->tokens = gwy_expr_transform_to_rpn_real(expr, expr->tokens, err);
    if (!expr->tokens) {
        g_assert(!err || *err);
        return FALSE;
    }

    if (expr->tokens->next) {
        g_set_error(err, GWY_EXPR_ERROR, GWY_EXPR_ERROR_GARBAGE,
                    _("Trailing garbage"));
        gwy_expr_token_list_delete(expr, expr->tokens);
        expr->tokens = NULL;
        return FALSE;
    }

    expr->in = gwy_expr_token_list_length(expr->tokens->rpn_block);
    if (expr->in > expr->ilen) {
        expr->ilen = expr->in;
        expr->input = g_renew(GwyExprCode, expr->input, expr->ilen);
    }
    for (t = expr->tokens->rpn_block, i = 0; t; t = t->next, i++) {
        expr->input[i].type = t->token;
        expr->input[i].value = t->value.v_float;
    }
    gwy_expr_token_list_delete(expr, expr->tokens);
    expr->tokens = NULL;

    if (!gwy_expr_stack_check_executability(expr)) {
        g_set_error(err, GWY_EXPR_ERROR, GWY_EXPR_ERROR_NOT_EXECUTABLE,
                    _("Stack is not executable"));
        return FALSE;
    }

    return TRUE;
}
