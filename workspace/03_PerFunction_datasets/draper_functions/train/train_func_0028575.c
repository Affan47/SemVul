close() {
    if (log_flags.gui_rpc_debug) {
        msg_printf(NULL, MSG_INFO,
            "[gui_rpc] closing GUI RPC listening socket %d\n", lsock
        );
    }
    if (lsock >= 0) {
        boinc_close_socket(lsock);
        lsock = -1;
    }
    for (unsigned int i=0; i<gui_rpcs.size(); i++) {
        delete gui_rpcs[i];
    }
    gui_rpcs.clear();
}
