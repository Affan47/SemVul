get_first_string(void) const
{
    CYG_REPORT_FUNCNAME("CdlProperty_StringVector::get_first_string");
    CYG_REPORT_FUNCARG1("this %p", this);
    CYG_PRECONDITION_THISC();

    std::string result;
    if (0 == data.size()) {
        result = "";
    } else {
        result = data[0];
    }
    CYG_REPORT_RETURN();
    return result;
}
