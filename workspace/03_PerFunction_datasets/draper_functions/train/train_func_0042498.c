read_archive_file(const char* path, RSS_FEED* rfp) {
    FILE* f = fopen(path, "r");
    if (!f) {
        if (log_flags.notice_debug) {
            msg_printf(0, MSG_INFO,
                "[notice] no archive file %s", path
            );
        }
        return 0;
    }
    MIOFILE fin;
    fin.init_file(f);
    XML_PARSER xp(&fin);
    while (!xp.get_tag()) {
        if (!xp.is_tag) continue;
        if (xp.match_tag("/notices")) {
            fclose(f);
            return 0;
        }
        if (xp.match_tag("notice")) {
            NOTICE n;
            int retval = n.parse(xp);
            if (retval) {
                if (log_flags.notice_debug) {
                    msg_printf(0, MSG_INFO,
                        "[notice] archive item parse error: %d", retval
                    );
                }
            } else {
                if (rfp) {
                    safe_strcpy(n.feed_url, rfp->url);
                    safe_strcpy(n.project_name, rfp->project_name);
                }
                append(n);
            }
        }
    }
    if (log_flags.notice_debug) {
        msg_printf(0, MSG_INFO, "[notice] archive parse error");
    }
    fclose(f);
    return ERR_XML_PARSE;
}
