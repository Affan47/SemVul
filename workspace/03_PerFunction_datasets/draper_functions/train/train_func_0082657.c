avahi_time_event_queue_new(const AvahiPoll *poll_api) {
    AvahiTimeEventQueue *q;

    if (!(q = avahi_new(AvahiTimeEventQueue, 1))) {
        avahi_log_error(__FILE__": Out of memory");
        goto oom;
    }

    q->poll_api = poll_api;

    if (!(q->prioq = avahi_prio_queue_new(compare)))
        goto oom;

    if (!(q->timeout = poll_api->timeout_new(poll_api, NULL, expiration_event, q)))
        goto oom;

    return q;

oom:

    if (q) {
        avahi_free(q);

        if (q->prioq)
            avahi_prio_queue_free(q->prioq);
    }

    return NULL;
}
