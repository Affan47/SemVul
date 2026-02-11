handle_project_attach_poll(GUI_RPC_CONN& grc) {
    unsigned int i;
    grc.mfout.printf(
        "<project_attach_reply>\n"
    );
    for (i=0; i<gstate.project_attach.messages.size(); i++) {
        grc.mfout.printf(
            "    <message>%s</message>\n",
            gstate.project_attach.messages[i].c_str()
        );
    }
    grc.mfout.printf(
        "    <error_num>%d</error_num>\n",
        gstate.project_attach.error_num
    );
    grc.mfout.printf(
        "</project_attach_reply>\n"
    );
}
