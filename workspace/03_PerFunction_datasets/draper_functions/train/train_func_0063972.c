Itcl_PushContext(interp, member, contextClass, contextObj, contextPtr)
    Tcl_Interp *interp;
    ItclMember *member;
    ItclClass *contextClass;
    ItclObject *contextObj;
    ItclContext *contextPtr;
{
    ItclCallFrame *framePtr = (ItclCallFrame *) &contextPtr->frame;

    int result, localCt, newEntry;
    ItclMemberCode *mcode;
    Proc *procPtr;
    Tcl_HashEntry *entry;


    result = Tcl_PushCallFrame(interp, (Tcl_CallFrame*)framePtr,
                 contextClass->namesp,  1);

    if (result != TCL_OK) {
        return result;
    }

    contextPtr->classDefn = contextClass;
    contextPtr->compiledLocals = &contextPtr->localStorage[0];


    if (contextObj) {
        entry = Tcl_CreateHashEntry(&contextClass->info->contextFrames,
            (char*)framePtr, &newEntry);

        Itcl_PreserveData((ClientData)contextObj);
        Tcl_SetHashValue(entry, (ClientData)contextObj);
    }


    if (member) {
        mcode = member->code;
        procPtr = mcode->procPtr;


        assert(mcode->procPtr->bodyPtr != NULL);

        result = TclProcCompileProc(interp, mcode->procPtr,
            mcode->procPtr->bodyPtr, (Namespace*)member->classDefn->namesp,
            "body for", member->fullname);

        if (result != TCL_OK) {
            return result;
        }


        localCt = procPtr->numCompiledLocals;
        if (localCt >
		(int)(sizeof(contextPtr->localStorage)/itclVarLocalSize)) {
            contextPtr->compiledLocals = (Var*)ckalloc(
                (unsigned)(localCt * itclVarLocalSize)
            );
        }


        framePtr->procPtr = procPtr;
        framePtr->numCompiledLocals = localCt;
        framePtr->compiledLocals = contextPtr->compiledLocals;

        TclInitCompiledLocals(interp, (CallFrame *) framePtr,
            (Namespace*)contextClass->namesp);
    }
    return result;
}
