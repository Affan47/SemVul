common_setup(void **testdata, void *handler)
{
    struct testdata_t *data;
    struct sigaction sa;

    data = malloc(sizeof(*data));
    if (!data) { return -1; }
    data->msg = strdup(MSG);
    if (!data->msg) { return -1; }

    data->handler = handler;
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    (void)sigaction(CR_SIGNUM, &sa, NULL);

    *testdata = data;
    return 0;
}
