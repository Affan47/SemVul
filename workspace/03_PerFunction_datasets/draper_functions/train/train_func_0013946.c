Jim_SetListIndex(Jim_Interp *interp, Jim_Obj *varNamePtr,
    Jim_Obj *const *indexv, int indexc, Jim_Obj *newObjPtr)
{
    Jim_Obj *varObjPtr, *objPtr, *listObjPtr;
    int shared, i, idx;

    varObjPtr = objPtr = Jim_GetVariable(interp, varNamePtr, JIM_ERRMSG | JIM_UNSHARED);
    if (objPtr == NULL)
        return JIM_ERR;
    if ((shared = Jim_IsShared(objPtr)))
        varObjPtr = objPtr = Jim_DuplicateObj(interp, objPtr);
    for (i = 0; i < indexc - 1; i++) {
        listObjPtr = objPtr;
        if (Jim_GetIndex(interp, indexv[i], &idx) != JIM_OK)
            goto err;
        if (Jim_ListIndex(interp, listObjPtr, idx, &objPtr, JIM_ERRMSG) != JIM_OK) {
            goto err;
        }
        if (Jim_IsShared(objPtr)) {
            objPtr = Jim_DuplicateObj(interp, objPtr);
            ListSetIndex(interp, listObjPtr, idx, objPtr, JIM_NONE);
        }
        Jim_InvalidateStringRep(listObjPtr);
    }
    if (Jim_GetIndex(interp, indexv[indexc - 1], &idx) != JIM_OK)
        goto err;
    if (ListSetIndex(interp, objPtr, idx, newObjPtr, JIM_ERRMSG) == JIM_ERR)
        goto err;
    Jim_InvalidateStringRep(objPtr);
    Jim_InvalidateStringRep(varObjPtr);
    if (Jim_SetVariable(interp, varNamePtr, varObjPtr) != JIM_OK)
        goto err;
    Jim_SetResult(interp, varObjPtr);
    return JIM_OK;
  err:
    if (shared) {
        Jim_FreeNewObj(interp, varObjPtr);
    }
    return JIM_ERR;
}
