Itk_ConfigClassOption(interp, contextObj, cdata, newval)
    Tcl_Interp *interp;
    ItclObject *contextObj;
    ClientData cdata;
    CONST char *newval;
{
    ItkClassOption *opt = (ItkClassOption*)cdata;
    int result = TCL_OK;
    ItclMemberCode *mcode;


    mcode = opt->member->code;
    if (mcode && mcode->procPtr->bodyPtr) {
        result = Itcl_EvalMemberCode(interp, (ItclMemberFunc*)NULL,
            opt->member, contextObj, 0, (Tcl_Obj**)NULL);
    }
    return result;
}
