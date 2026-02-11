update_update_keys_file_for_nextwindow_syntax_changes(FbTk::ResourceManager& rm,
        const FbTk::FbString& keyfilename, const FbTk::FbString& appsfilename) {

    string whole_keyfile = read_file(keyfilename);

    size_t pos = 0;
    while (true) {
        const char *keyfile = whole_keyfile.c_str();
        const char *loc = 0;
        size_t old_pos = pos;

        if ((loc = FbTk::StringUtil::strcasestr(keyfile + old_pos,
                        "nextwindow")))
            pos = (loc - keyfile) + 10;
        if ((loc = FbTk::StringUtil::strcasestr(keyfile + old_pos,
                        "prevwindow")))
            pos = (pos > old_pos && keyfile + pos < loc) ?
                pos : (loc - keyfile) + 10;
        if ((loc = FbTk::StringUtil::strcasestr(keyfile + old_pos,
                        "nextgroup")))
            pos = (pos > old_pos && keyfile + pos < loc) ?
                pos : (loc - keyfile) + 9;
        if ((loc = FbTk::StringUtil::strcasestr(keyfile + old_pos,
                        "prevgroup")))
            pos = (pos > old_pos && keyfile + pos < loc) ?
                pos : (loc - keyfile) + 9;
        if (pos == old_pos)
            break;

        pos = whole_keyfile.find_first_not_of(" \t", pos);
        if (pos != std::string::npos && isdigit(whole_keyfile[pos])) {
            char *endptr = 0;
            unsigned int mask = strtoul(keyfile + pos, &endptr, 0);
            string insert = "";
            if ((mask & 9) == 9)
                insert = "{static groups}";
            else if (mask & 1)
                insert = "{groups}";
            else if (mask & 8)
                insert = "{static}";
            if (mask & 2)
                insert += " (stuck=no)";
            if (mask & 4)
                insert += " (shaded=no)";
            if (mask & 16)
                insert += " (minimized=no)";
            if (mask)
                whole_keyfile.replace(pos, endptr - keyfile - pos, insert);
        }
    }

    write_file(keyfilename, whole_keyfile);
}
