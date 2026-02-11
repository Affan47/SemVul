HtmlCssStyleSheetFree(pStyle)
    CssStyleSheet *pStyle;
{
    if (pStyle) {
        CssPriority *pPriority;


        freeRulesList(&pStyle->pUniversalRules);
        freeRulesList(&pStyle->pAfterRules);
        freeRulesList(&pStyle->pBeforeRules);
        freeRulesHash(&pStyle->aByTag);
        freeRulesHash(&pStyle->aByClass);
        freeRulesHash(&pStyle->aById);


        pPriority = pStyle->pPriority;
        while (pPriority) {
            CssPriority *pNext = pPriority->pNext;
            Tcl_DecrRefCount(pPriority->pIdTail);
            HtmlFree(pPriority);
            pPriority = pNext;
        }

        HtmlFree(pStyle);
    }
}
