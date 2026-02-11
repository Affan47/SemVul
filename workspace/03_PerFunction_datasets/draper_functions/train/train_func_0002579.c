event_handler(int fd, short which, void *arg) {
    conn *c;

    c = (conn *)arg;
    c->which = which;


    if (fd != c->sfd) {
        if (settings.verbose > 0)
            fprintf(stderr, "Catastrophic: event fd doesn't match conn fd!\n");
        conn_close(c);
        return;
    }


    drive_machine(c);


    return;
}
