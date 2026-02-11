array_cmd_size(Jim_Interp *interp, int argc, Jim_Obj *const *argv)
{
    Jim_Obj *objPtr;
    int len = 0;


    objPtr = Jim_GetVariable(interp, argv[0], JIM_NONE);
    if (objPtr) {
        len = Jim_DictSize(interp, objPtr);
        if (len < 0) {
            return JIM_ERR;
        }
    }

    Jim_SetResultInt(interp, len);

    return JIM_OK;
}
