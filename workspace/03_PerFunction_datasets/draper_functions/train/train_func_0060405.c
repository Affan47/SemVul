Jim_EvalNamespace(Jim_Interp *interp, Jim_Obj *scriptObj, Jim_Obj *nsObj)
{
    Jim_CallFrame *callFramePtr;
    int retcode;


    callFramePtr = JimCreateCallFrame(interp, interp->framePtr, nsObj);
    callFramePtr->argv = &interp->emptyObj;
    callFramePtr->argc = 0;
    callFramePtr->procArgsObjPtr = NULL;
    callFramePtr->procBodyObjPtr = scriptObj;
    callFramePtr->staticVars = NULL;
    callFramePtr->fileNameObj = interp->emptyObj;
    callFramePtr->line = 0;
    Jim_IncrRefCount(scriptObj);
    interp->framePtr = callFramePtr;


    if (interp->framePtr->level == interp->maxCallFrameDepth) {
        Jim_SetResultString(interp, "Too many nested calls. Infinite recursion?", -1);
        retcode = JIM_ERR;
    }
    else {

        retcode = Jim_EvalObj(interp, scriptObj);
    }


    interp->framePtr = interp->framePtr->parent;
    if (callFramePtr->vars.size != JIM_HT_INITIAL_SIZE) {
        JimFreeCallFrame(interp, callFramePtr, JIM_FCF_NONE);
    }
    else {
        JimFreeCallFrame(interp, callFramePtr, JIM_FCF_NOHT);
    }

    return retcode;
}
