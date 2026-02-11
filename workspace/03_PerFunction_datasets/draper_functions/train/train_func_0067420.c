Jim_UnsetCoreCommand(Jim_Interp *interp, int argc, Jim_Obj *const *argv)
{
    int i = 1;
    int complain = 1;

    while (i < argc) {
        if (Jim_CompareStringImmediate(interp, argv[i], "--")) {
            i++;
            break;
        }
        if (Jim_CompareStringImmediate(interp, argv[i], "-nocomplain")) {
            complain = 0;
            i++;
            continue;
        }
        break;
    }

    while (i < argc) {
        if (Jim_UnsetVariable(interp, argv[i], complain ? JIM_ERRMSG : JIM_NONE) != JIM_OK
            && complain) {
            return JIM_ERR;
        }
        i++;
    }
    return JIM_OK;
}
