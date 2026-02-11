erase_status_tag(const char *uname, const char *tag, int options)
{
    int rc = pcmk_ok;
    char xpath[STATUS_PATH_MAX];
    int cib_opts = cib_quorum_override | cib_xpath | options;

    if (fsa_cib_conn && uname) {
        snprintf(xpath, STATUS_PATH_MAX, "//node_state[@uname='%s']/%s", uname, tag);
        crm_info("Deleting xpath: %s", xpath);
        rc = fsa_cib_conn->cmds->delete(fsa_cib_conn, xpath, NULL, cib_opts);
        fsa_register_cib_callback(rc, FALSE, strdup(xpath), erase_xpath_callback);
    }
}
