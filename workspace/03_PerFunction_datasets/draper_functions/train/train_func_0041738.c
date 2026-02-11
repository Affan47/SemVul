LetBlock(JSContext *cx, JSTokenStream *ts, JSTreeContext *tc, JSBool statement)
{
    JSParseNode *pn, *pnblock, *pnlet;
    JSStmtInfo stmtInfo;

    JS_ASSERT(CURRENT_TOKEN(ts).type == TOK_LET);


    pnlet = NewParseNode(PN_BINARY, tc);
    if (!pnlet)
        return NULL;

    MUST_MATCH_TOKEN(TOK_LP, JSMSG_PAREN_BEFORE_LET);


    pnblock = PushLexicalScope(cx, ts, tc, &stmtInfo);
    if (!pnblock)
        return NULL;
    pn = pnblock;
    pn->pn_expr = pnlet;

    pnlet->pn_left = Variables(cx, ts, tc, true);
    if (!pnlet->pn_left)
        return NULL;
    pnlet->pn_left->pn_xflags = PNX_POPVAR;

    MUST_MATCH_TOKEN(TOK_RP, JSMSG_PAREN_AFTER_LET);

    ts->flags |= TSF_OPERAND;
    if (statement && !js_MatchToken(cx, ts, TOK_LC)) {


        pn = NewParseNode(PN_UNARY, tc);
        if (!pn)
            return NULL;
        pn->pn_type = TOK_SEMI;
        pn->pn_num = -1;
        pn->pn_kid = pnblock;

        statement = JS_FALSE;
    }
    ts->flags &= ~TSF_OPERAND;

    if (statement) {
        pnlet->pn_right = Statements(cx, ts, tc);
        if (!pnlet->pn_right)
            return NULL;
        MUST_MATCH_TOKEN(TOK_RC, JSMSG_CURLY_AFTER_LET);
    } else {


        pnblock->pn_op = JSOP_LEAVEBLOCKEXPR;
        pnlet->pn_right = AssignExpr(cx, ts, tc);
        if (!pnlet->pn_right)
            return NULL;
    }

    PopStatement(tc);
    return pn;
}
