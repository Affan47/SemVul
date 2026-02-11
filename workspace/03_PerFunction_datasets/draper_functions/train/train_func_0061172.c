overflowBoxCb(pItem, origin_x, origin_y, pOverflow, clientData)
    HtmlCanvasItem *pItem;
    int origin_x;
    int origin_y;
    Overflow *pOverflow;
    ClientData clientData;
{
    OverflowBox *p = (OverflowBox *)clientData;
    if (p->isFound) return 0;

    if (pOverflow && p->pNode == pOverflow->pItem->pNode) {
        *p->pX = pOverflow->x;
        *p->pY = pOverflow->y;
        *p->pW = pOverflow->w;
        *p->pH = pOverflow->h;
        p->isFound = 1;
    }
    return 0;
}
