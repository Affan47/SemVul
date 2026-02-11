update_event(conn *c, int new_flags) {
    if (c->ev_flags == new_flags)
        return 1;
    if (event_del(&c->event) == -1) return 0;
    event_set(&c->event, c->sfd, new_flags, event_handler, (void *)c);
    c->ev_flags = new_flags;
    if (event_add(&c->event, 0) == -1) return 0;
    return 1;
}
