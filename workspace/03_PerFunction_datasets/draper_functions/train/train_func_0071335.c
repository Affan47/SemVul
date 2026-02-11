Jim_UplevelCoreCommand(Jim_Interp *interp, int argc, Jim_Obj *const *argv)
{
    if (argc >= 2) {
        int retcode;
        Jim_CallFrame *savedCallFrame, *targetCallFrame;
        Jim_Obj *objPtr;
        const char *str;


        savedCallFrame = interp->framePtr;


        str = Jim_String(argv[1]);
        if ((str[0] >= '0' && str[0] <= '9') || str[0] == '#') {
            targetCallFrame =Jim_GetCallFrameByLevel(interp, argv[1]);
            argc--;
            argv++;
        }
        else {
            targetCallFrame = Jim_GetCallFrameByLevel(interp, NULL);
        }
        if (targetCallFrame == NULL) {
            return JIM_ERR;
        }
        if (argc < 2) {
            argv--;
            Jim_WrongNumArgs(interp, 1, argv, "?level? command ?arg ...?");
            return JIM_ERR;
        }

        interp->framePtr = targetCallFrame;
        if (argc == 2) {
            retcode = Jim_EvalObj(interp, argv[1]);
        }
        else {
            objPtr = Jim_ConcatObj(interp, argc - 1, argv + 1);
            Jim_IncrRefCount(objPtr);
            retcode = Jim_EvalObj(interp, objPtr);
            Jim_DecrRefCount(interp, objPtr);
        }
        interp->framePtr = savedCallFrame;
        return retcode;
    }
    else {
        Jim_WrongNumArgs(interp, 1, argv, "?level? command ?arg ...?");
        return JIM_ERR;
    }
}
