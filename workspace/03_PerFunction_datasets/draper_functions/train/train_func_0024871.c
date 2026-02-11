selectorFree(pSelector)
    CssSelector *pSelector;
{
    if( !pSelector ) return;
    selectorFree(pSelector->pNext);
    HtmlFree(pSelector->zValue);
    HtmlFree(pSelector->zAttr);
    HtmlFree(pSelector);
}
