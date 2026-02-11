set_value_format(CdlSimpleValue& val1, CdlSimpleValue& val2)
{
    CYG_REPORT_FUNCNAME("CdlSimpleValue::set_value_format");
    CYG_REPORT_FUNCARG3XV(this, &val1, &val2);

    format = (CdlValueFormat_Default != val1.format) ? val1.format : val2.format;

    CYG_REPORT_RETURN();
}
