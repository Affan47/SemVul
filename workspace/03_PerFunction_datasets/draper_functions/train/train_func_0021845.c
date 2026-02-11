get_messages(int seqno, MESSAGES& msgs, bool translatable) {
    int retval;
    SET_LOCALE sl;
    char buf[256];
    RPC rpc(this);

    sprintf(buf,
        "<get_messages>\n"
        "  <seqno>%d</seqno>\n"
        "%s"
        "</get_messages>\n",
        seqno,
        translatable?"  <translatable/>\n":""
    );

    retval = rpc.do_rpc(buf);
    if (!retval) {
        while (!rpc.xp.get_tag()) {
            if (rpc.xp.match_tag("/msgs")) {
                return 0;
            }
            if (rpc.xp.match_tag("msg")) {
                MESSAGE* message = new MESSAGE();
                message->parse(rpc.xp);
                msgs.messages.push_back(message);
                continue;
            }
            if (rpc.xp.match_tag("boinc_gui_rpc_reply")) continue;
            if (rpc.xp.match_tag("msgs")) continue;

        }
    }
    return retval;
}
