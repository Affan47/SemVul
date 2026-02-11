target_enable(CdlInterpreter interp, int argc, const char* argv[])
{
    CYG_REPORT_FUNCNAMETYPE("CdlDbParser::target_enable", "result %d");
    CYG_REPORT_FUNCARG1XV(argc);
    CYG_PRECONDITION_CLASSC(interp);

    std::string name = interp->get_variable(dbparser_targetname);
    CYG_ASSERTC("" != name);
    CdlPackagesDatabaseBody::target_data* target =
        static_cast<CdlPackagesDatabaseBody::target_data*>(interp->get_assoc_data(dbparser_targetdata));


    if (2 != argc) {
        CdlParse::report_error(interp, diag_target + name, "`enable' should be followed by a list of CDL options.");
    } else {
        int          list_count     = 0;
        const char** list_entries   = 0;
        Tcl_Interp* tcl_interp      = interp->get_tcl_interpreter();
        if (TCL_OK != Tcl_SplitList(tcl_interp, CDL_TCL_CONST_CAST(char*, argv[1]), &list_count, CDL_TCL_CONST_CAST(char***, &list_entries))) {
            CdlParse::report_error(interp, diag_target + name, Tcl_GetStringResult(tcl_interp));
        } else {
            for (int i = 0; i < list_count; i++) {
                target->enable.push_back(list_entries[i]);
            }
            Tcl_Free((char *) list_entries);
        }
    }

    CYG_REPORT_RETVAL(TCL_OK);
    return TCL_OK;
}
