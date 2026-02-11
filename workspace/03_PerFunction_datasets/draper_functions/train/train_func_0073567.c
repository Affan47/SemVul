ruleFree(pRule)
    CssRule *pRule;
{
    if (pRule) {
        if (pRule->freeSelector) {
            selectorFree(pRule->pSelector);
        }
        if (pRule->freePropertySets) {
            propertySetFree(pRule->pPropertySet);
        }
        HtmlFree(pRule);
    }
}
