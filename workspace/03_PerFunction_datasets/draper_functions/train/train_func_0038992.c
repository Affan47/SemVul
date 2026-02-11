handle_acct_mgr_info(GUI_RPC_CONN& grc) {
    grc.mfout.printf(
        "<acct_mgr_info>\n"
        "   <acct_mgr_url>%s</acct_mgr_url>\n"
        "   <acct_mgr_name>%s</acct_mgr_name>\n",
        gstate.acct_mgr_info.master_url,
        gstate.acct_mgr_info.project_name
    );

    if (strlen(gstate.acct_mgr_info.login_name)) {
        grc.mfout.printf("   <have_credentials/>\n");
    }

    if (gstate.acct_mgr_info.cookie_required) {
        grc.mfout.printf("   <cookie_required/>\n");
        grc.mfout.printf(
            "   <cookie_failure_url>%s</cookie_failure_url>\n",
            gstate.acct_mgr_info.cookie_failure_url
        );
    }

    grc.mfout.printf("</acct_mgr_info>\n");
}
