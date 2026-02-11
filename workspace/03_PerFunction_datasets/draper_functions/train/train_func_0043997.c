create_slave(CdlLoadable loadable_arg, bool safe)
{
    CYG_REPORT_FUNCNAMETYPE("CdlInterpreter::create_slave", "slave %p");
    CYG_REPORT_FUNCARG3XV(this, loadable_arg, safe);
    CYG_PRECONDITION_THISC();
    CYG_PRECONDITION(0 == parent, "slave interpreters cannot be created inside slaves");
    CYG_PRECONDITION(0 != toplevel, "CDL's slave interpreters need an associated toplevel");
    CYG_PRECONDITION_CLASSC(loadable_arg);


    static cdl_int      next_slave = 1;
    std::string         slave_name;
    Cdl::integer_to_string(next_slave++, slave_name);
    slave_name = "slave" + slave_name;


#if 0
    Tcl_Interp* slave = Tcl_CreateSlave(interp, CDL_TCL_CONST_CAST(char*, slave_name.c_str()), safe);
#else
    Tcl_Interp* slave = Tcl_CreateInterp();
#endif
    if (0 == slave) {
        throw std::bad_alloc();
    }

    CdlInterpreter result = 0;
    try {
        result = new CdlInterpreterBody(slave);
    }
    catch(std::bad_alloc) {
        Tcl_DeleteInterp(slave);
        throw;
    }
    result->owns_interp = true;
#if 0
    try {
        slaves.push_back(result);
    }
    catch(std::bad_alloc) {
        delete result;
        throw;
    }
#endif

    result->parent      = this;
    result->set_toplevel(toplevel);
    result->loadable    = loadable_arg;
    result->set_variable("cdl_version", get_variable("cdl_version"));
    result->set_variable("cdl_interactive", get_variable("cdl_interactive"));

    CYG_POSTCONDITION_CLASSC(result);
    CYG_REPORT_RETVAL(result);
    return result;
}
