simple_setup(void **testdata)
{
    char msg[] = MSG;
    void *p;

    CRUT_DEBUG("Initializing simple.");
    CRUT_DEBUG("sizeof(msg) = %d", (int)sizeof(msg)+1);
    p = malloc(sizeof(msg)+1);
    if (p == NULL) { return -1; }
    memcpy(p, msg, sizeof(msg)+1);
    *testdata = p;

    return 0;
}
