add_property_parsers(std::vector<CdlInterpreterCommandEntry>& parsers)
{
    CYG_REPORT_FUNCNAME("CdlUserVisible::add_property_parsers");

    static CdlInterpreterCommandEntry commands[] =
    {
        CdlInterpreterCommandEntry("display",     &parse_display),
        CdlInterpreterCommandEntry("description", &parse_description),
        CdlInterpreterCommandEntry("doc",         &parse_doc),
        CdlInterpreterCommandEntry("",            0)
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
    CdlNodeBody::add_property_parsers(parsers);

    CYG_REPORT_RETURN();
}
