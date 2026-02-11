HtmlStyleCounter(pTree, zName)
    HtmlTree *pTree;
    const char *zName;
{
    int ii;
    StyleApply *p = (StyleApply *)(pTree->pStyleApply);

    for (ii = p->nCounter - 1; ii >= 0; ii--) {
        if (0 == strcmp(zName, p->apCounter[ii]->zName)) {
            return p->apCounter[ii]->iValue;
        }
    }

    return 0;
}
