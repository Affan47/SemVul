Statements(JSContext *cx, JSTokenStream *ts, JSTreeContext *tc)
{
    JSParseNode *pn, *pn2, *saveBlock;
    JSTokenType tt;

    JS_CHECK_RECURSION(cx, return NULL);

    pn = NewParseNode(PN_LIST, tc);
    if (!pn)
        return NULL;
    pn->pn_type = TOK_LC;
    pn->makeEmpty();
    pn->pn_blockid = tc->blockid();
    saveBlock = tc->blockNode;
    tc->blockNode = pn;

    for (;;) {
        ts->flags |= TSF_OPERAND;
        tt = js_PeekToken(cx, ts);
        ts->flags &= ~TSF_OPERAND;
        if (tt <= TOK_EOF || tt == TOK_RC) {
            if (tt == TOK_ERROR) {
                if (ts->flags & TSF_EOF)
                    ts->flags |= TSF_UNEXPECTED_EOF;
                return NULL;
            }
            break;
        }
        pn2 = Statement(cx, ts, tc);
        if (!pn2) {
            if (ts->flags & TSF_EOF)
                ts->flags |= TSF_UNEXPECTED_EOF;
            return NULL;
        }

        if (pn2->pn_type == TOK_FUNCTION) {


            if (tc->atTopLevel())
                pn->pn_xflags |= PNX_FUNCDEFS;
            else
                tc->flags |= TCF_HAS_FUNCTION_STMT;
        }
        pn->append(pn2);
    }


    if (tc->blockNode != pn)
        pn = tc->blockNode;
    tc->blockNode = saveBlock;

    pn->pn_pos.end = CURRENT_TOKEN(ts).pos.end;
    return pn;
}
