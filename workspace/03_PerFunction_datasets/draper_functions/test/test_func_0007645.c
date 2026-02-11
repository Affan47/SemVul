is_propagation_required() const
{
    CYG_REPORT_FUNCNAMETYPE("CdlTransaction::is_propagation_required", "result %d");
    CYG_REPORT_FUNCARG1XV(this);
    CYG_PRECONDITION_THISC();

    bool result = false;

    if ((0 != value_changes.size()) || (0 != active_changes.size())) {
        result = true;
    }

    CYG_REPORT_RETVAL(result);
    return result;
}
