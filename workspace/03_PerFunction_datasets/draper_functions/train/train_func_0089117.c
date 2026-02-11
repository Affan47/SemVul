avahi_simple_poll_new(void) {
    AvahiSimplePoll *s;

    if (!(s = avahi_new(AvahiSimplePoll, 1)))
        return NULL;

    if (pipe(s->wakeup_pipe) < 0) {
        avahi_free(s);
        return NULL;
    }

    set_nonblock(s->wakeup_pipe[0]);
    set_nonblock(s->wakeup_pipe[1]);

    s->api.userdata = s;

    s->api.watch_new = watch_new;
    s->api.watch_free = watch_free;
    s->api.watch_update = watch_update;
    s->api.watch_get_events = watch_get_events;

    s->api.timeout_new = timeout_new;
    s->api.timeout_free = timeout_free;
    s->api.timeout_update = timeout_update;

    s->pollfds = NULL;
    s->max_pollfds = s->n_pollfds = 0;
    s->rebuild_pollfds = 1;
    s->quit = 0;
    s->n_watches = 0;
    s->events_valid = 0;

    s->watch_req_cleanup = 0;
    s->timeout_req_cleanup = 0;

    s->prepared_timeout = 0;

    s->state = STATE_INIT;

    s->wakeup_issued = 0;

    avahi_simple_poll_set_func(s, NULL, NULL);

    AVAHI_LLIST_HEAD_INIT(AvahiWatch, s->watches);
    AVAHI_LLIST_HEAD_INIT(AvahiTimeout, s->timeouts);

    return s;
}
