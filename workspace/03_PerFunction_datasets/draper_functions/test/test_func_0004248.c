Jim_String(Jim_Obj *objPtr)
{
    if (objPtr->bytes == NULL) {

        JimPanic((objPtr->typePtr->updateStringProc == NULL, "UpdateStringProc called against '%s' type.", objPtr->typePtr->name));
        objPtr->typePtr->updateStringProc(objPtr);
    }
    return objPtr->bytes;
}
