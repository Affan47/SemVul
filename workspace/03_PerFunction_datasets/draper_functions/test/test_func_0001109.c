handle_set_host_info(GUI_RPC_CONN& grc) {
    while (!grc.xp.get_tag()) {
        if (grc.xp.match_tag("host_info")) {
            HOST_INFO hi;
            int retval = hi.parse(grc.xp);
            if (retval) {
                grc.mfout.printf("<error>host_info parse error</error>\n");
                return;
            }
            if (strlen(hi.product_name)) {
                safe_strcpy(gstate.host_info.product_name, hi.product_name);
            }
            grc.mfout.printf("<success/>\n");
            gstate.set_client_state_dirty("set_host_info RPC");
            return;
        }
    }
    grc.mfout.printf("<error>Missing host_info</error>\n");
}
