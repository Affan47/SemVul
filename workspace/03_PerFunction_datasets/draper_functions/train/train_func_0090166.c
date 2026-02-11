Jim_DictAddElement(Jim_Interp *interp, Jim_Obj *objPtr,
    Jim_Obj *keyObjPtr, Jim_Obj *valueObjPtr)
{
    int retcode;

    JimPanic((Jim_IsShared(objPtr), "Jim_DictAddElement called with shared object"));
    if (SetDictFromAny(interp, objPtr) != JIM_OK) {
        return JIM_ERR;
    }
    retcode = DictAddElement(interp, objPtr, keyObjPtr, valueObjPtr);
    Jim_InvalidateStringRep(objPtr);
    return retcode;
}
