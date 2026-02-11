DrawInfoCmd(char *data, int len) {
    int color = atoi(data);
    char *buf;

    (void)len;

    buf = strchr(data, ' ');
    if (!buf) {
        LOG(LOG_WARNING, "common::DrawInfoCmd", "got no data");
        buf = "";
    } else {
        buf++;
    }
    draw_ext_info(color, MSG_TYPE_CLIENT, MSG_TYPE_CLIENT_COMMAND, buf);
}
