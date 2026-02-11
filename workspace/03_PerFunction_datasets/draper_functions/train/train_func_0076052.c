normalFlowMarginQuery(pNormal)
    NormalFlow *pNormal;
{
    int iMargin = pNormal->iMinMargin + pNormal->iMaxMargin;
    if (pNormal->nonegative) {
        iMargin = MAX(0, iMargin);
    }
    return iMargin;
}
