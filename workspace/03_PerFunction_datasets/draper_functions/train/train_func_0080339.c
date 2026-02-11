h_conn(const int fd, const short which, conn c)
{
    if (fd != c->sock.fd) {
        twarnx("Argh! event fd doesn't match conn fd.");
        close(fd);
        conn_close(c);
        update_conns();
        return;
    }

    if (which == 'h') {
        dbgprintf("client hung up fd=%d\n", fd);
        conn_close(c);
        return;
    }

    conn_data(c);
    while (cmd_data_ready(c) && (c->cmd_len = cmd_len(c))) do_cmd(c);
    update_conns();
}
