quits_sent() {
    for (unsigned int i=0; i<gui_rpcs.size(); i++) {
        GUI_RPC_CONN* gr = gui_rpcs[i];
        if (gr->au_ss_state == AU_SS_QUIT_REQ) return false;
        if (gr->au_mgr_state == AU_MGR_QUIT_REQ) return false;
    }
    return true;
}
