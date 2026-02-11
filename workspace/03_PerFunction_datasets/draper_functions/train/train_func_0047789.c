HtmlCssSelectorComma(pParse)
    CssParse *pParse;
{
    int n = (pParse->nXtra + 1) * sizeof(CssSelector *);


    if (pParse->isIgnore) return;

    pParse->apXtraSelector = (CssSelector **)HtmlRealloc(
           "CssParse.apXtraSelector", (char *)pParse->apXtraSelector, n
    );
    pParse->apXtraSelector[pParse->nXtra] = pParse->pSelector;
    pParse->pSelector = 0;
    pParse->nXtra++;
}
