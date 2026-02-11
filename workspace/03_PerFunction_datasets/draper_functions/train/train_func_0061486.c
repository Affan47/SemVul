HtmlGetInlineBorder(pLayout, pContext, pNode)
    LayoutContext *pLayout;
    InlineContext *pContext;
    HtmlNode *pNode;
{
    InlineBorder *pBorder = 0;

    pBorder = HtmlNew(InlineBorder);


    if (pContext->pCurrent) {
        nodeGetBoxProperties(pLayout, pNode, 0,&pBorder->box);
        nodeGetMargins(pLayout, pNode, 0, &pBorder->margin);
    }


    inlineBoxMetrics(pContext, pNode, &pBorder->metrics);

    pBorder->pNode = pNode;
    return pBorder;
}
