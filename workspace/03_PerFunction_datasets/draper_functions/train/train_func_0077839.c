NewBinary(JSTokenType tt, JSOp op, JSParseNode *left, JSParseNode *right,
          JSTreeContext *tc)
{
    JSParseNode *pn, *pn1, *pn2;

    if (!left || !right)
        return NULL;


    if (PN_TYPE(left) == tt &&
        PN_OP(left) == op &&
        (js_CodeSpec[op].format & JOF_LEFTASSOC)) {
        if (left->pn_arity != PN_LIST) {
            pn1 = left->pn_left, pn2 = left->pn_right;
            left->pn_arity = PN_LIST;
            left->pn_parens = false;
            left->initList(pn1);
            left->append(pn2);
            if (tt == TOK_PLUS) {
                if (pn1->pn_type == TOK_STRING)
                    left->pn_xflags |= PNX_STRCAT;
                else if (pn1->pn_type != TOK_NUMBER)
                    left->pn_xflags |= PNX_CANTFOLD;
                if (pn2->pn_type == TOK_STRING)
                    left->pn_xflags |= PNX_STRCAT;
                else if (pn2->pn_type != TOK_NUMBER)
                    left->pn_xflags |= PNX_CANTFOLD;
            }
        }
        left->append(right);
        left->pn_pos.end = right->pn_pos.end;
        if (tt == TOK_PLUS) {
            if (right->pn_type == TOK_STRING)
                left->pn_xflags |= PNX_STRCAT;
            else if (right->pn_type != TOK_NUMBER)
                left->pn_xflags |= PNX_CANTFOLD;
        }
        return left;
    }


    if (tt == TOK_PLUS &&
        left->pn_type == TOK_NUMBER &&
        right->pn_type == TOK_NUMBER) {
        left->pn_dval += right->pn_dval;
        left->pn_pos.end = right->pn_pos.end;
        RecycleTree(right, tc);
        return left;
    }

    pn = NewOrRecycledNode(tc);
    if (!pn)
        return NULL;
    InitParseNode(pn, tt, op, PN_BINARY);
    pn->pn_pos.begin = left->pn_pos.begin;
    pn->pn_pos.end = right->pn_pos.end;
    pn->pn_left = left;
    pn->pn_right = right;
    return pn;
}
