pty_request(ssh_session session, ssh_channel channel,
                       const char *term, int cols, int rows, int py, int px,
                       void *userdata) {
    struct channel_data_struct *cdata = (struct channel_data_struct *)userdata;

    (void) session;
    (void) channel;
    (void) term;

    cdata->winsize->ws_row = rows;
    cdata->winsize->ws_col = cols;
    cdata->winsize->ws_xpixel = px;
    cdata->winsize->ws_ypixel = py;

    if (openpty(&cdata->pty_master, &cdata->pty_slave, NULL, NULL,
                cdata->winsize) != 0) {
        fprintf(stderr, "Failed to open pty\n");
        return SSH_ERROR;
    }
    return SSH_OK;
}
