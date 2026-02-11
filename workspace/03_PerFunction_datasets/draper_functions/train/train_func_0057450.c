get_double_value() const
{
    CYG_REPORT_FUNCNAME("CdlSimpleValue::get_double_value");
    CYG_REPORT_FUNCARG1XV(this);

    double result = 0.0;
    if ((valid_flags & double_valid) || has_double_value()) {
        result = double_value;
    }

    CYG_REPORT_RETURN();
    return result;
}
