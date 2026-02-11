cssParse(
pTree, n, z, isStyle, origin, pStyleId, pImportCmd, pUrlCmd, pErrorVar, ppStyle)
    HtmlTree *pTree;
    int n;
    CONST char *z;
    int isStyle;
    int origin;
    Tcl_Obj *pStyleId;
    Tcl_Obj *pImportCmd;
    Tcl_Obj *pUrlCmd;
    Tcl_Obj *pErrorVar;
    CssStyleSheet **ppStyle;
{
    CssParse sParse;
    int ii;

    memset(&sParse, 0, sizeof(CssParse));
    sParse.origin = origin;
    sParse.pStyleId = pStyleId;
    sParse.pImportCmd = pImportCmd;
    sParse.pUrlCmd = pUrlCmd;
    sParse.interp = (pTree ? pTree->interp : 0);
    sParse.pTree = pTree;
    if (pErrorVar) {
        sParse.pErrorLog = Tcl_NewObj();
        Tcl_IncrRefCount(sParse.pErrorLog);
    }

    if( n<0 ){
        n = strlen(z);
    }


    if (0==*ppStyle) {
        sParse.pStyle = HtmlNew(CssStyleSheet);


        if (pStyleId) {
            Tcl_InitHashTable(&sParse.pStyle->aByTag, TCL_STRING_KEYS);
            Tcl_InitHashTable(&sParse.pStyle->aByClass, TCL_STRING_KEYS);
            Tcl_InitHashTable(&sParse.pStyle->aById, TCL_STRING_KEYS);
        }
    } else {
        sParse.pStyle = *ppStyle;
    }


    if (pStyleId) {
        sParse.pPriority1 = newCssPriority(sParse.pStyle, origin, pStyleId, 0);
        sParse.pPriority2 = newCssPriority(sParse.pStyle, origin, pStyleId, 1);
    }

    if (isStyle) {
        HtmlCssRunStyleParser(z, n, &sParse);
    } else {
        HtmlCssRunParser(z, n, &sParse);
    }

    *ppStyle = sParse.pStyle;


    selectorFree(sParse.pSelector);
    for (ii = 0; ii < sParse.nXtra; ii++) {
        selectorFree(sParse.apXtraSelector[ii]);
    }
    propertySetFree(sParse.pPropertySet);
    propertySetFree(sParse.pImportant);

    if (pErrorVar) {
        Tcl_ObjSetVar2(pTree->interp, pErrorVar, 0, sParse.pErrorLog, 0);
        Tcl_DecrRefCount(sParse.pErrorLog);
    }

    return 0;
}
