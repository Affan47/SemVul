handle_get_cc_config(GUI_RPC_CONN& grc) {
    string s;
    int retval = read_file_string(CONFIG_FILE, s);
    if (!retval) {
        strip_whitespace(s);
        grc.mfout.printf("%s\n", s.c_str());
    }
}
