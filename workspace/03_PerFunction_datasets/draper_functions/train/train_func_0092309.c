ObjToKeyedListEntry (interp, objPtr, entryPtr)
    Tcl_Interp  *interp;
    Tcl_Obj     *objPtr;
    keylEntry_t *entryPtr;
{
    int objc;
    Tcl_Obj **objv;
    char *key;
    int keyLen;

    if (Tcl_ListObjGetElements (interp, objPtr, &objc, &objv) != TCL_OK) {
        Tcl_ResetResult (interp);
        Tcl_AppendStringsToObj (Tcl_GetObjResult (interp),
                                "keyed list entry not a valid list, ",
                                "found \"",
                                Tcl_GetStringFromObj (objPtr, NULL),
                                "\"", (char *) NULL);
        return TCL_ERROR;
    }

    if (objc != 2) {
        Tcl_AppendStringsToObj (Tcl_GetObjResult (interp),
                                "keyed list entry must be a two ",
                                "element list, found \"",
                                Tcl_GetStringFromObj (objPtr, NULL),
                                "\"", (char *) NULL);
        return TCL_ERROR;
    }

    key = Tcl_GetStringFromObj (objv [0], &keyLen);
    if (ValidateKey (interp, key, keyLen, FALSE) == TCL_ERROR) {
        return TCL_ERROR;
    }

    entryPtr->key = ckstrdup (key);
    entryPtr->valuePtr = Tcl_DuplicateObj (objv [1]);
    Tcl_IncrRefCount (entryPtr->valuePtr);

    return TCL_OK;
}
