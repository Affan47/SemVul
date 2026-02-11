remove_dups(NOTICE& n) {
    deque<NOTICE>::iterator i = notices.begin();
    bool removed_something = false;
    bool retval = true;
    double min_time = gstate.now - 30*86400;
    while (i != notices.end()) {
        NOTICE& n2 = *i;
        if (n2.arrival_time < min_time
            || (n2.create_time && n2.create_time < min_time)
        ) {
            i = notices.erase(i);
            removed_something = true;
        } else if (same_guid(n, n2)) {
            n2.keep = true;
            return false;
        } else if (same_text(n, n2)) {
            int min_diff = 0;


            if (!strcmp(n.category, "scheduler")) {
                min_diff = 7*86400;
            }

            if (n.create_time > n2.create_time + min_diff) {
                i = notices.erase(i);
                removed_something = true;
            } else {
                n2.keep = true;
                retval = false;
                ++i;
            }
        } else {
            ++i;
        }
    }
#ifndef SIM
    if (removed_something) {
        gstate.gui_rpcs.set_notice_refresh();
    }
#endif
    return retval;
}
