insertRule(ppList, pRule)
    CssRule **ppList;
    CssRule *pRule;
{
    if (!*ppList || ruleCompare(*ppList, pRule) <= 0) {


        pRule->pNext = *ppList;
        *ppList = pRule;
    } else {


        CssRule *pR = *ppList;
        while (pR->pNext && ruleCompare(pR->pNext, pRule)>0 ) {
            pR = pR->pNext;
        }
        pRule->pNext = pR->pNext;
        pR->pNext = pRule;
    }
}
