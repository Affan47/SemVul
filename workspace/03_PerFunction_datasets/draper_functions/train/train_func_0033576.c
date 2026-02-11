HtmlCssTclNodeDynamics(interp, pNode)
    Tcl_Interp *interp;
    HtmlNode *pNode;
{
    Tcl_Obj *pRet = Tcl_NewObj();
    if (!HtmlNodeIsText(pNode)) {
        CssDynamic *p;
        HtmlElementNode *pElem = (HtmlElementNode *)pNode;
        for (p = pElem->pDynamic; p ; p = p->pNext) {
            Tcl_Obj *pOther = Tcl_NewObj();
            HtmlCssSelectorToString(p->pSelector, pOther);
            Tcl_ListObjAppendElement(0, pRet, pOther);
        }
    }
    Tcl_SetObjResult(interp, pRet);
    return TCL_OK;
}
