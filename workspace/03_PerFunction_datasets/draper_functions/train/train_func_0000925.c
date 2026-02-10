set_value(std::string val, CdlValueFormat new_format)
{
    CYG_REPORT_FUNCNAME("CdlSimpleValue::set_value (string)");
    CYG_REPORT_FUNCARG1XV(this);

    value               = val;
    int_value           = 0;
    double_value        = 0.0;
    valid_flags         = string_valid;
    format              = new_format;
}
