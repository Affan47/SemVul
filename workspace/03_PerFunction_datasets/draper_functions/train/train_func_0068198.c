JimCreateCallFrame(Jim_Interp *interp, Jim_CallFrame *parent, Jim_Obj *nsObj)
{
    Jim_CallFrame *cf;

    if (interp->freeFramesList) {
        cf = interp->freeFramesList;
        interp->freeFramesList = cf->next;
    }
    else {
        cf = Jim_Alloc(sizeof(*cf));
        cf->vars.table = NULL;
    }

    cf->id = interp->callFrameEpoch++;
    cf->parent = parent;
    cf->level = parent ? parent->level + 1 : 0;
    cf->argv = NULL;
    cf->argc = 0;
    cf->procArgsObjPtr = NULL;
    cf->procBodyObjPtr = NULL;
    cf->next = NULL;
    cf->staticVars = NULL;
    cf->localCommands = NULL;

    cf->nsObj = nsObj;
    Jim_IncrRefCount(nsObj);
    if (cf->vars.table == NULL)
        Jim_InitHashTable(&cf->vars, &JimVariablesHashTableType, interp);
    return cf;
}
