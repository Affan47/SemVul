remove_command(std::string name)
{
    CYG_REPORT_FUNCNAME("CdlInterpreter::remove_command");
    CYG_REPORT_FUNCARG1XV(this);
    CYG_PRECONDITION_THISC();
    CYG_PRECONDITIONC("" != name);

    if (0 != Tcl_DeleteCommand(tcl_interp, CDL_TCL_CONST_CAST(char*, name.c_str()))) {
        CYG_FAIL("attempt to delete non-existant command");
    }
    CYG_REPORT_RETURN();
}
