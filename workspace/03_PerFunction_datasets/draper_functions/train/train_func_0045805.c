parse_define_final_check(CdlInterpreter interp, CdlProperty_String prop)
{
    CYG_REPORT_FUNCNAME("parse_define_final_check");
    CYG_PRECONDITION_CLASSC(prop);
    CYG_PRECONDITION_CLASSC(interp);

    const std::string& str = prop->get_string();

    if (!Cdl::is_valid_c_preprocessor_symbol(str)) {
        CdlParse::report_property_parse_error(interp, prop, str + " is not a valid C preprocessor symbol");
    }


    std::string file_option = prop->get_option("file");
    if (("" != file_option) && ("system.h" != file_option)) {
        CdlParse::report_property_parse_error(interp, prop, "Invalid -file option " + file_option);
    }


    CYG_REPORT_RETURN();
}
