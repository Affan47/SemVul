NewOrRecycledNode(JSTreeContext *tc)
{
    JSParseNode *pn, *pn2;

    pn = tc->compiler->nodeList;
    if (!pn) {
        JSContext *cx = tc->compiler->context;

        JS_ARENA_ALLOCATE_TYPE(pn, JSParseNode, &cx->tempPool);
        if (!pn)
            js_ReportOutOfScriptQuota(cx);
    } else {
        tc->compiler->nodeList = pn->pn_next;


        switch (pn->pn_arity) {
          case PN_FUNC:
            RecycleTree(pn->pn_body, tc);
            break;
          case PN_LIST:
            pn2 = pn->pn_head;
            if (pn2) {
                while (pn2 && !pn2->pn_used && !pn2->pn_defn)
                    pn2 = pn2->pn_next;
                if (pn2) {
                    pn2 = pn->pn_head;
                    do {
                        pn2 = RecycleTree(pn2, tc);
                    } while (pn2);
                } else {
                    *pn->pn_tail = tc->compiler->nodeList;
                    tc->compiler->nodeList = pn->pn_head;
#ifdef METER_PARSENODES
                    recyclednodes += pn->pn_count;
#endif
                    break;
                }
            }
            break;
          case PN_TERNARY:
            RecycleTree(pn->pn_kid1, tc);
            RecycleTree(pn->pn_kid2, tc);
            RecycleTree(pn->pn_kid3, tc);
            break;
          case PN_BINARY:
            if (pn->pn_left != pn->pn_right)
                RecycleTree(pn->pn_left, tc);
            RecycleTree(pn->pn_right, tc);
            break;
          case PN_UNARY:
            RecycleTree(pn->pn_kid, tc);
            break;
          case PN_NAME:
            if (!pn->pn_used)
                RecycleTree(pn->pn_expr, tc);
            break;
          case PN_NULLARY:
            break;
        }
    }
    if (pn) {
#ifdef METER_PARSENODES
        parsenodes++;
        if (parsenodes - recyclednodes > maxparsenodes)
            maxparsenodes = parsenodes - recyclednodes;
#endif
        pn->pn_used = pn->pn_defn = false;
        memset(&pn->pn_u, 0, sizeof pn->pn_u);
        pn->pn_next = NULL;
    }
    return pn;
}
