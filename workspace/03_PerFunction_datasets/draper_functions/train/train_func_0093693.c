parse(XML_PARSER& xp) {
    url = "";
    email_addr = "";
    passwd_hash = "";
    user_name = "";
    team_name = "";

    while (!xp.get_tag()) {
        if (xp.parse_string("url", url)) continue;
        if (xp.parse_string("email_addr", email_addr)) continue;
        if (xp.parse_string("passwd_hash", passwd_hash)) continue;
        if (xp.parse_string("user_name", user_name)) continue;
        if (xp.parse_string("team_name", team_name)) continue;
    }
    canonicalize_master_url(url);
}
