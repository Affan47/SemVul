parse(XML_PARSER& xp) {
    std::string msg;
    clear();
    while (!xp.get_tag()) {
        if (xp.match_tag("/project_attach_reply")) return 0;
        if (xp.parse_int("error_num", error_num)) continue;
        if (xp.parse_string("message", msg)) {
            messages.push_back(msg);
            continue;
        }
    }
    return ERR_XML_PARSE;
}
