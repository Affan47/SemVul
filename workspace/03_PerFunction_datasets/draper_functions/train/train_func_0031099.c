Jim_EvalObjVector(Jim_Interp *interp, int objc, Jim_Obj *const *objv)
{
    int i, retcode;


    for (i = 0; i < objc; i++)
        Jim_IncrRefCount(objv[i]);

    retcode = JimInvokeCommand(interp, objc, objv);


    for (i = 0; i < objc; i++)
        Jim_DecrRefCount(interp, objv[i]);

    return retcode;
}
