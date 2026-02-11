parse_string_property(CdlInterpreter interp, int argc, const char* argv[], std::string name,
                                char** options_desc, void (*final_parser)(CdlInterpreter, CdlProperty_String))
{
    CYG_REPORT_FUNCNAME("parse_string_property");
    CYG_PRECONDITION_CLASSC(interp);

    CdlProperty_String new_property = 0;

    try {
        std::vector<std::pair<std::string,std::string> > options;
        int data_index = CdlParse::parse_options(interp, property_string + argv[0], options_desc, argc, argv, 1, options);

        if (data_index == argc) {
            CdlParse::report_property_parse_error(interp, argv[0], "Missing argument.");
        } else if ((data_index + 1) < argc) {
            CdlParse::report_property_parse_error(interp, argv[0], std::string("Too many arguments, expecting just one."));
        } else {

            CdlNode current_node = interp->get_node();
            CYG_ASSERTC(0 != current_node);
            new_property = CdlProperty_StringBody::make(current_node, name, argv[data_index], argc, argv, options);
            if (0 != final_parser) {
                (*final_parser)(interp, new_property);
            }
        }
    } catch(...) {
        if (0 != new_property) {
            delete new_property;
        }
        throw;
    }

    CYG_REPORT_RETURN();
    return TCL_OK;
}

