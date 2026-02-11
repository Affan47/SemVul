CdlParentableBody()
{
    CYG_REPORT_FUNCNAME("CdlParentable:: default constructor");
    CYG_REPORT_FUNCARG1XV(this);

    change_parent_save_position = -1;
    cdlparentablebody_cookie  = CdlParentableBody_Magic;
    CYGDBG_MEMLEAK_CONSTRUCTOR();

    CYG_POSTCONDITION_THISC();
    CYG_REPORT_RETURN();
}
