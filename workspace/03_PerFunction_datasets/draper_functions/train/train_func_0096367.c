RebindLets(JSParseNode *pn, JSTreeContext *tc)
{
    if (!pn)
        return true;

    switch (pn->pn_arity) {
      case PN_LIST:
        for (JSParseNode *pn2 = pn->pn_head; pn2; pn2 = pn2->pn_next)
            RebindLets(pn2, tc);
        break;

      case PN_TERNARY:
        RebindLets(pn->pn_kid1, tc);
        RebindLets(pn->pn_kid2, tc);
        RebindLets(pn->pn_kid3, tc);
        break;

      case PN_BINARY:
        RebindLets(pn->pn_left, tc);
        RebindLets(pn->pn_right, tc);
        break;

      case PN_UNARY:
        RebindLets(pn->pn_kid, tc);
        break;

      case PN_FUNC:
        RebindLets(pn->pn_body, tc);
        break;

      case PN_NAME:
        RebindLets(pn->maybeExpr(), tc);

        if (pn->pn_defn) {
            JS_ASSERT(pn->pn_blockid > tc->topStmt->blockid);
        } else if (pn->pn_used) {
            if (pn->pn_lexdef->pn_blockid == tc->topStmt->blockid) {
                ForgetUse(pn);

                JSAtomListElement *ale = tc->decls.lookup(pn->pn_atom);
                if (ale) {
                    while ((ale = ALE_NEXT(ale)) != NULL) {
                        if (ALE_ATOM(ale) == pn->pn_atom) {
                            LinkUseToDef(pn, ALE_DEFN(ale), tc);
                            return true;
                        }
                    }
                }

                ale = tc->lexdeps.lookup(pn->pn_atom);
                if (!ale) {
                    ale = MakePlaceholder(pn, tc);
                    if (!ale)
                        return NULL;

                    JSDefinition *dn = ALE_DEFN(ale);
                    dn->pn_type = TOK_NAME;
                    dn->pn_op = JSOP_NOP;
                }
                LinkUseToDef(pn, ALE_DEFN(ale), tc);
            }
        }
        break;

      case PN_NAMESET:
        RebindLets(pn->pn_tree, tc);
        break;
    }

    return true;
}
