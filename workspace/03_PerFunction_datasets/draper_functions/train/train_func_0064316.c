ForgetUse(JSParseNode *pn)
{
    if (!pn->pn_used) {
        JS_ASSERT(!pn->pn_defn);
        return;
    }

    JSParseNode **pnup = &pn->lexdef()->dn_uses;
    JSParseNode *pnu;
    while ((pnu = *pnup) != pn)
        pnup = &pnu->pn_link;
    *pnup = pn->pn_link;
    pn->pn_used = false;
}
