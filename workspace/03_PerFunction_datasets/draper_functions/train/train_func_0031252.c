Itk_CreateClassOption(interp, cdefn, switchName, resName, resClass,
    defVal, config, optPtr)

    Tcl_Interp *interp;
    ItclClass *cdefn;
    char *switchName;
    char *resName;
    char *resClass;
    char *defVal;
    char *config;
    ItkClassOption **optPtr;
{
    ItkClassOption *opt;
    ItclMemberCode *mcode;


    if (config) {
        if (Itcl_CreateMemberCode(interp, cdefn, (char*)NULL, config,
            &mcode) != TCL_OK) {

            return TCL_ERROR;
        }
        Itcl_PreserveData((ClientData)mcode);
        Itcl_EventuallyFree((ClientData)mcode, Itcl_DeleteMemberCode);
    }
    else {
        mcode = NULL;
    }


    opt = (ItkClassOption*)ckalloc(sizeof(ItkClassOption));
    opt->member = Itcl_CreateMember(interp, cdefn, switchName);
    opt->member->code = mcode;

    opt->resName = (char*)ckalloc((unsigned)(strlen(resName)+1));
    strcpy(opt->resName, resName);

    opt->resClass = (char*)ckalloc((unsigned)(strlen(resClass)+1));
    strcpy(opt->resClass, resClass);

    opt->init = (char*)ckalloc((unsigned)(strlen(defVal)+1));
    strcpy(opt->init, defVal);

    *optPtr = opt;
    return TCL_OK;
}
