JimReferencesHTValDestructor(void *interp, void *val)
{
    Jim_Reference *refPtr = (void *)val;

    Jim_DecrRefCount(interp, refPtr->objPtr);
    if (refPtr->finalizerCmdNamePtr != NULL) {
        Jim_DecrRefCount(interp, refPtr->finalizerCmdNamePtr);
    }
    Jim_Free(val);
}
