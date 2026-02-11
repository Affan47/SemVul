HtmlCssImport(pParse, pToken)
    CssParse *pParse;
    CssToken *pToken;
{
    Tcl_Obj *pEval = pParse->pImportCmd;


    if (pParse->isBody) return;

    if (pEval) {
        Tcl_Interp *interp = pParse->interp;
        CssProperty *p = tokenToProperty(pParse, pToken);
        CONST char *zUrl = p->v.zVal;

        switch (p->eType) {
            case CSS_TYPE_URL:
                break;
            case CSS_TYPE_RAW:
            case CSS_TYPE_STRING:
                if (pParse && pParse->pUrlCmd) {
                    doUrlCmd(pParse, zUrl, strlen(zUrl));
                    zUrl = Tcl_GetStringResult(pParse->interp);
                }
                break;
            default:
                return;
        }

        pEval = Tcl_DuplicateObj(pEval);
        Tcl_IncrRefCount(pEval);
        Tcl_ListObjAppendElement(interp, pEval, Tcl_NewStringObj(zUrl, -1));
        Tcl_EvalObjEx(interp, pEval, TCL_EVAL_GLOBAL|TCL_EVAL_DIRECT);
        Tcl_DecrRefCount(pEval);
        HtmlFree(p);
    }
}
