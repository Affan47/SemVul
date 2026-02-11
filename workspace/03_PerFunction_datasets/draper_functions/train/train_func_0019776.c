initialize_savefile_support(CdlToplevel toplevel)
{
    CYG_REPORT_FUNCNAME("CdlOption::initialize_savefile_support");

    toplevel->add_savefile_command("cdl_option", 0, &savefile_option_command);
    CdlValuableBody::initialize_savefile_support(toplevel, "cdl_option");

    CYG_REPORT_RETURN();
}
