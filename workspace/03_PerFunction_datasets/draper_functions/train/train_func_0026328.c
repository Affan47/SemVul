Rivet_InitServerVariables( Tcl_Interp *interp, apr_pool_t *pool )
{
    int     ap_mpm_result;
    Tcl_Obj *obj;

    obj = Tcl_NewStringObj(ap_server_root, -1);
    Tcl_IncrRefCount(obj);
    Tcl_SetVar2Ex(interp,
            "server",
            "SERVER_ROOT",
            obj,
            TCL_GLOBAL_ONLY);
    Tcl_DecrRefCount(obj);

    obj = Tcl_NewStringObj(ap_server_root_relative(pool,SERVER_CONFIG_FILE), -1);
    Tcl_IncrRefCount(obj);
    Tcl_SetVar2Ex(interp,
            "server",
            "SERVER_CONF",
            obj,
            TCL_GLOBAL_ONLY);
    Tcl_DecrRefCount(obj);

    obj = Tcl_NewStringObj(ap_server_root_relative(pool, RIVET_DIR), -1);
    Tcl_IncrRefCount(obj);
    Tcl_SetVar2Ex(interp,
            "server",
            "RIVET_DIR",
            obj,
            TCL_GLOBAL_ONLY);
    Tcl_DecrRefCount(obj);

    obj = Tcl_NewStringObj(ap_server_root_relative(pool, RIVET_INIT), -1);
    Tcl_IncrRefCount(obj);
    Tcl_SetVar2Ex(interp,
            "server",
            "RIVET_INIT",
            obj,
            TCL_GLOBAL_ONLY);
    Tcl_DecrRefCount(obj);

#if RIVET_DISPLAY_VERSION
    obj = Tcl_NewStringObj(RIVET_VERSION, -1);
    Tcl_IncrRefCount(obj);
    Tcl_SetVar2Ex(interp,
            "server",
            "RIVET_VERSION",
            obj,
            TCL_GLOBAL_ONLY);
    Tcl_DecrRefCount(obj);
#endif

    if (ap_mpm_query(AP_MPMQ_IS_THREADED,&ap_mpm_result) == APR_SUCCESS)
    {
        switch (ap_mpm_result)
        {
            case AP_MPMQ_STATIC:
                obj = Tcl_NewStringObj("static", -1);
                break;
            case AP_MPMQ_NOT_SUPPORTED:
                obj = Tcl_NewStringObj("unsupported", -1);
                break;
            default:
                obj = Tcl_NewStringObj("undefined", -1);
                break;
        }
        Tcl_IncrRefCount(obj);
        Tcl_SetVar2Ex(interp,"server","MPM_THREADED",obj,TCL_GLOBAL_ONLY);
        Tcl_DecrRefCount(obj);
    }

    if (ap_mpm_query(AP_MPMQ_IS_FORKED,&ap_mpm_result) == APR_SUCCESS)
    {
        switch (ap_mpm_result)
        {
            case AP_MPMQ_STATIC:
                obj = Tcl_NewStringObj("static", -1);
                break;
            case AP_MPMQ_DYNAMIC:
                obj = Tcl_NewStringObj("dynamic", -1);
                break;
            default:
                obj = Tcl_NewStringObj("undefined", -1);
                break;
        }
        Tcl_IncrRefCount(obj);
        Tcl_SetVar2Ex(interp,"server","MPM_FORKED",obj,TCL_GLOBAL_ONLY);
        Tcl_DecrRefCount(obj);
    }
}
