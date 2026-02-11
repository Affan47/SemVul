parse_group(CdlInterpreter interp, int argc, const char* argv[])
{
    CYG_REPORT_FUNCNAMETYPE("parse_group", "result %d");

    int result = CdlParse::parse_string_property(interp, argc, argv, CdlPropertyId_Group, 0, 0);

    CYG_REPORT_RETVAL(result);
    return result;
}
