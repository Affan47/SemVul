find_relative_file(std::string filename, std::string dirname) const
{
    CYG_REPORT_FUNCNAME("CdlLoadable::find_relative_file");
    CYG_REPORT_FUNCARG1XV(this);
    CYG_PRECONDITION_THISC();
    CYG_PRECONDITIONC("" != filename);


    interp->set_variable("::cdl_topdir",  get_toplevel()->get_directory());
    interp->set_variable("::cdl_pkgdir",  directory);
    interp->set_variable("::cdl_prefdir", dirname);
    interp->set_variable("::cdl_target",  filename);

    std::string result;
    int tmp = interp->eval(find_relative_file_script, result);
    if (tmp != TCL_OK) {
        result = "";
    }


    for (unsigned int i = 0; i < result.size(); i++) {
        if ('\\' == result[i]) {
            result[i] = '/';
        }
    }

    CYG_REPORT_RETURN();
    return result;
}
