Jim_LrepeatCoreCommand(Jim_Interp *interp, int argc, Jim_Obj *const *argv)
{
    Jim_Obj *objPtr;
    long count;

    if (argc < 2 || Jim_GetLong(interp, argv[1], &count) != JIM_OK || count < 0) {
        Jim_WrongNumArgs(interp, 1, argv, "count ?value ...?");
        return JIM_ERR;
    }

    if (count == 0 || argc == 2) {
        return JIM_OK;
    }

    argc -= 2;
    argv += 2;

    objPtr = Jim_NewListObj(interp, argv, argc);
    while (--count) {
        ListInsertElements(objPtr, -1, argc, argv);
    }

    Jim_SetResult(interp, objPtr);
    return JIM_OK;
}
