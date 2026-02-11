add_legal_values_change(CdlValuable valuable)
{
    CYG_REPORT_FUNCNAME("CdlTransaction::add_legal_values_change");
    CYG_REPORT_FUNCARG2XV(this, valuable);
    CYG_PRECONDITION_THISC();
    CYG_PRECONDITION_CLASSC(valuable);

    legal_values_changes.insert(valuable);

    CYG_REPORT_RETURN();
}
