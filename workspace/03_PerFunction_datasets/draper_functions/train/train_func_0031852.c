parse(XML_PARSER& xp) {
    clear();
    string msg;
    while (!xp.get_tag()) {
        if (xp.match_tag("/acct_mgr_rpc_reply")) return 0;
        if (xp.parse_int("error_num", error_num)) continue;
        if (xp.parse_string("message", msg)) {
            messages.push_back(msg);
            continue;
        }
    }
    return ERR_XML_PARSE;
}
