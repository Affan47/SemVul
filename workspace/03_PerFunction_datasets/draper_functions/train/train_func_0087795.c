hashstatsCmd(clientData, interp, objc, objv)
    ClientData clientData;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
{
    HtmlTree *pTree = (HtmlTree *)clientData;
    Tcl_HashEntry *p;
    Tcl_HashSearch search;
    int nObj = 0;
    int nRef = 0;
    char zRes[128];

    for (
        p = Tcl_FirstHashEntry(&pTree->aValues, &search);
        p;
        p = Tcl_NextHashEntry(&search)
    ) {
        HtmlComputedValues *pV =
            (HtmlComputedValues *)Tcl_GetHashKey(&pTree->aValues, p);
        nObj++;
        nRef += pV->nRef;
    }

    sprintf(zRes, "%d %d", nObj, nRef);
    Tcl_SetResult(interp, zRes, TCL_VOLATILE);
    return TCL_OK;
}
