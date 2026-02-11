command_terminate(char * token, Channel * c) {
    char id[256];
    int err = 0;

    json_read_string(&c->inp, id, sizeof(id));
    if (read_stream(&c->inp) != 0) exception(ERR_JSON_SYNTAX);
    if (read_stream(&c->inp) != MARKER_EOM) exception(ERR_JSON_SYNTAX);

    if (terminate_debug_context(c, id2ctx(id)) != 0) err = errno;

    send_simple_result(c, token, err);
}
