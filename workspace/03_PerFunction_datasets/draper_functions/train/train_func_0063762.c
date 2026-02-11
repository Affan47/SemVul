ws_expr_symbol(WsCompiler *compiler, WsUInt32 line,
                             char *identifier)
{
    WsExpression *expr = expr_alloc(compiler, WS_EXPR_SYMBOL, line);

    if (expr) {
        expr->u.symbol = ws_f_strdup(compiler->pool_stree, identifier);
        if (expr->u.symbol == NULL)
            ws_error_memory(compiler);
    }

    ws_lexer_free_block(compiler, identifier);

    return expr;
}
