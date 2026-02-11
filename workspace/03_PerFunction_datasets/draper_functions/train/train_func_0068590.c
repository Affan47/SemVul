add_property_parsers(std::vector<CdlInterpreterCommandEntry>& parsers)
{
    CYG_REPORT_FUNCNAME("CdlBuildLoadable::add_property_parsers");

    static CdlInterpreterCommandEntry commands[] =
    {
        CdlInterpreterCommandEntry("library",            &CdlBuildLoadableBody::parse_library       ),
        CdlInterpreterCommandEntry("makefile",           &CdlBuildLoadableBody::parse_makefile      ),
        CdlInterpreterCommandEntry("include_dir",        &CdlBuildLoadableBody::parse_include_dir   ),
        CdlInterpreterCommandEntry("include_files",      &CdlBuildLoadableBody::parse_include_files ),
        CdlInterpreterCommandEntry("",                   0                                          )
    };

    for (int i = 0; commands[i].command != 0; i++) {
        std::vector<CdlInterpreterCommandEntry>::const_iterator j;
        for (j = parsers.begin(); j != parsers.end(); j++) {
            if (commands[i].name == j->name) {
                if (commands[i].command != j->command) {
                    CYG_FAIL("Property names are being re-used");
                }
                break;
            }
        }
        if (j == parsers.end()) {
            parsers.push_back(commands[i]);
        }
    }

    CYG_REPORT_RETURN();
}
