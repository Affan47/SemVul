load_rc(BScreen &screen) {

    _FB_USES_NLS;
    string dbfile(getRcFilename());

    XrmDatabaseHelper database;

    database = XrmGetFileDatabase(dbfile.c_str());
    if (database==0)
        database = XrmGetFileDatabase(DEFAULT_INITFILE);


    screen.removeWorkspaceNames();

    std::string screen_number = FbTk::StringUtil::number2String(screen.screenNumber());

    std::string name_lookup("session.screen");
    name_lookup += screen_number;
    name_lookup += ".workspaceNames";
    std::string class_lookup("session.screen");
    class_lookup += screen_number;
    class_lookup += ".WorkspaceNames";

    XrmValue value;
    char *value_type;
    if (XrmGetResource(*database, name_lookup.c_str(), class_lookup.c_str(), &value_type,
                       &value)) {

        string values(value.addr);
        BScreen::WorkspaceNames names;

        StringUtil::removeTrailingWhitespace(values);
        StringUtil::removeFirstWhitespace(values);
        StringUtil::stringtok<BScreen::WorkspaceNames>(names, values, ",");
        BScreen::WorkspaceNames::iterator it;
        for(it = names.begin(); it != names.end(); ++it) {
            if (!(*it).empty() && (*it) != "")
            screen.addWorkspaceName((*it).c_str());
        }

    }

    if (!dbfile.empty()) {
        if (!m_screen_rm.load(dbfile.c_str())) {
            cerr<<_FB_CONSOLETEXT(Fluxbox, CantLoadRCFile, "Failed to load database", "Failed trying to read rc file")<<":"<<dbfile<<endl;
            cerr<<_FB_CONSOLETEXT(Fluxbox, CantLoadRCFileTrying, "Retrying with", "Retrying rc file loading with (the following file)")<<": "<<DEFAULT_INITFILE<<endl;
            if (!m_screen_rm.load(DEFAULT_INITFILE))
                cerr<<_FB_CONSOLETEXT(Fluxbox, CantLoadRCFile, "Failed to load database", "")<<": "<<DEFAULT_INITFILE<<endl;
        }
    } else {
        if (!m_screen_rm.load(DEFAULT_INITFILE))
            cerr<<_FB_CONSOLETEXT(Fluxbox, CantLoadRCFile, "Failed to load database", "")<<": "<<DEFAULT_INITFILE<<endl;
    }
}
