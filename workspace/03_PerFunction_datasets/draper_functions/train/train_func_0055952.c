iperf_test_reset(struct iperf_test *test)
{
    struct iperf_stream *sp;

    close(test->ctrl_sck);


    while (!SLIST_EMPTY(&test->streams)) {
        sp = SLIST_FIRST(&test->streams);
        SLIST_REMOVE_HEAD(&test->streams, streams);
        iperf_free_stream(sp);
    }
    if (test->timer != NULL) {
	tmr_cancel(test->timer);
	test->timer = NULL;
    }
    if (test->stats_timer != NULL) {
	tmr_cancel(test->stats_timer);
	test->stats_timer = NULL;
    }
    if (test->reporter_timer != NULL) {
	tmr_cancel(test->reporter_timer);
	test->reporter_timer = NULL;
    }
    test->done = 0;

    SLIST_INIT(&test->streams);

    test->role = 's';
    set_protocol(test, Ptcp);
    test->omit = OMIT;
    test->duration = DURATION;
    test->diskfile_name = (char*) 0;
    test->affinity = -1;
    test->server_affinity = -1;
    test->title = NULL;
    test->congestion = NULL;
    test->state = 0;
    test->server_hostname = NULL;

    test->ctrl_sck = -1;
    test->prot_listener = -1;

    test->bytes_sent = 0;

    test->reverse = 0;
    test->sender = 0;
    test->sender_has_retransmits = 0;
    test->no_delay = 0;

    FD_ZERO(&test->read_set);
    FD_ZERO(&test->write_set);
    FD_SET(test->listener, &test->read_set);
    test->max_fd = test->listener;

    test->num_streams = 1;
    test->settings->socket_bufsize = 0;
    test->settings->blksize = DEFAULT_TCP_BLKSIZE;
    test->settings->rate = 0;
    test->settings->mss = 0;
    memset(test->cookie, 0, COOKIE_SIZE);
}
