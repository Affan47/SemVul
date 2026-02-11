is_member(double val, bool allow_conversions) const
{
    CYG_REPORT_FUNCNAMETYPE("CdlListValue::is_member (double)", "result %d");
    CYG_REPORT_FUNCARG3XV(this, &val, allow_conversions);
    CYG_PRECONDITION_THISC();

    bool result = false;
    for (std::vector<CdlSimpleValue>::const_iterator val_i = table.begin(); val_i != table.end(); val_i++) {
        if (val_i->has_double_value() && (val_i->get_double_value() == val)) {
            result = true;
            break;
        }
    }
    if (!result) {
        for (std::vector<std::pair<double,double> >::const_iterator i = double_ranges.begin();
             i != double_ranges.end(); i++) {
            if ((val >= i->first) && (val <= i->second)) {
                result = true;
                break;
            }
        }
    }
    if (!result && allow_conversions) {
        cdl_int integer_value;
        if (Cdl::double_to_integer(val, integer_value)) {
            result = is_member(integer_value, false);
        }
    }

    CYG_REPORT_RETVAL(result);
    return result;
}
