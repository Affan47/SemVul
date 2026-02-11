HtmlCssFreeDynamics(pElem)
    HtmlElementNode *pElem;
{
    CssDynamic *p = pElem->pDynamic;
    while (p) {
        CssDynamic *pTmp = p;
        p = p->pNext;
        HtmlFree(pTmp);
    }
    pElem->pDynamic = 0;
}
