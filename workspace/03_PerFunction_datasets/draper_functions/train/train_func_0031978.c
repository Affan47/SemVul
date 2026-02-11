handle_msgs_to_host() {
    DB_MSG_TO_HOST mth;
    char buf[256];
    sprintf(buf, "where hostid = %d and handled = %d", g_reply->host.id, 0);
    while (!mth.enumerate(buf)) {
        g_reply->msgs_to_host.push_back(mth);
        mth.handled = true;
        mth.update();
    }
}
