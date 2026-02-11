layoutBboxCb(pItem, origin_x, origin_y, pOverflow, clientData)
    HtmlCanvasItem *pItem;
    int origin_x;
    int origin_y;
    Overflow *pOverflow;
    ClientData clientData;
{
    int x, y, w, h;
    LayoutBboxQuery *pQuery = (LayoutBboxQuery *)clientData;
    HtmlNode *pNode;

    pNode = itemToBox(pItem, origin_x, origin_y, &x, &y, &w, &h);
    if (pOverflow) {
        x -= pOverflow->xscroll;
        y -= pOverflow->yscroll;
    }


    for (; pNode; pNode = HtmlNodeParent(pNode)) {
        if (pNode == pQuery->pNode) {
            pQuery->left = MIN(pQuery->left, x);
            pQuery->top = MIN(pQuery->top, y);
            pQuery->right = MAX(pQuery->right, x + w);
            pQuery->bottom = MAX(pQuery->bottom, y + h);
        }
    }
    return 0;
}
