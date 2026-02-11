HtmlFloatListLog(pTree, zCaption, zNode, pList)
    HtmlTree *pTree;
    CONST char *zCaption;
    CONST char *zNode;
    HtmlFloatList *pList;
{
    char zBuf[1024];
    FloatListEntry *pCsr;
    int y = pList->yorigin;
    int x = pList->xorigin;

    Tcl_Obj *pLog = Tcl_NewObj();
    Tcl_IncrRefCount(pLog);

    sprintf(zBuf, "<p>Origin point is (%d, %d).</p>", x, y);
    Tcl_AppendToObj(pLog, zBuf, -1);
    Tcl_AppendToObj(pLog,"<table><tr><th>Left<th>Top (y)<th>Right<th>isTop",-1);
    for (pCsr = pList->pEntry; pCsr; pCsr = pCsr->pNext) {
        char zLeft[20];
        char zRight[20];
        strcpy(zLeft, "N/A");
        strcpy(zRight, "N/A");

        if (pCsr->leftValid)  { sprintf(zLeft, "%d", pCsr->left - x); }
        if (pCsr->rightValid) { sprintf(zRight, "%d", pCsr->right - x); }

        sprintf(zBuf, "<tr><td>%s<td>%d<td>%s<td>%d",
            zLeft, pCsr->y - y, zRight, pCsr->isTop);
        Tcl_AppendToObj(pLog, zBuf, -1);
    }
    sprintf(zBuf, "<tr><td>N/A<td>%d<td>N/A</table>", pList->yend - y);
    Tcl_AppendToObj(pLog, zBuf, -1);

    HtmlLog(pTree, "LAYOUTENGINE", "%s %s %s",
        zNode, zCaption, Tcl_GetString(pLog)
    );

    Tcl_DecrRefCount(pLog);
}
