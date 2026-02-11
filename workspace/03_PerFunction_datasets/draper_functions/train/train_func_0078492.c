get_variable(std::string name)
{
    CYG_REPORT_FUNCNAME("CdlInterpreter::get_variable");
    CYG_REPORT_FUNCARG2("this %p, name %s", this, name.c_str());
    CYG_PRECONDITION_THISC();
    CYG_PRECONDITIONC("" != name);

    std::string result = "";
    const char *tmp = Tcl_GetVar(tcl_interp, CDL_TCL_CONST_CAST(char*, name.c_str()), TCL_GLOBAL_ONLY);
    if (0 != tmp) {
        result = tmp;
    }

    CYG_REPORT_RETURN();
    return result;
}

