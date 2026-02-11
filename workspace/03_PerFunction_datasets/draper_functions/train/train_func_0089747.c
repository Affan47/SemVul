ws_stmt_for(WsCompilerPtr compiler, WsUInt32 line, WsList *init,
                         WsExpression *e1, WsExpression *e2, WsExpression *e3,
                         WsStatement *stmt_body)
{
    WsStatement *stmt = stmt_alloc(compiler, WS_STMT_FOR, line, line);

    if (stmt) {
        stmt->u.s_for.init = init;
        stmt->u.s_for.e1 = e1;
        stmt->u.s_for.e2 = e2;
        stmt->u.s_for.e3 = e3;
        stmt->u.s_for.stmt = stmt_body;
    }

    return stmt;
}
