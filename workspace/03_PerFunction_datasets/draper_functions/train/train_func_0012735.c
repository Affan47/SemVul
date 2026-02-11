Jim_CollectCoreCommand(Jim_Interp *interp, int argc, Jim_Obj *const *argv)
{
    if (argc != 1) {
        Jim_WrongNumArgs(interp, 1, argv, "");
        return JIM_ERR;
    }
    Jim_SetResultInt(interp, Jim_Collect(interp));


    while (interp->freeList) {
        Jim_Obj *nextObjPtr = interp->freeList->nextObjPtr;
        Jim_Free(interp->freeList);
        interp->freeList = nextObjPtr;
    }

    return JIM_OK;
}
