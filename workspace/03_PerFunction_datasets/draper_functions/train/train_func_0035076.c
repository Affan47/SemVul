parse_stop_string() {
    const char* c = OPTIONS.get_arg_string(GMARGFLAG_STOP_STRING);
    if (c == NULL) return;

    char* d = strdup(c);
    char* p = strtok(d, ".");
    if (p == NULL) {
        goto error_return;
    }
    gm_stop_major = atoi(p);
    p = strtok(NULL, ".");
    if (p != NULL) gm_stop_minor = atoi(p);

    if (gm_stop_major == 0) {
        goto error_return;
    }
    if (gm_stop_minor == 0) {
        printf("stopping after stage %d\n", gm_stop_major);
    } else {
        printf("stopping at stage %d.%d\n", gm_stop_major, gm_stop_minor);
    }
    error_return: free(d);
}
